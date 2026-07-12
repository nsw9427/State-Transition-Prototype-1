#include <stdio.h>
#include <math.h>

typedef enum {
    LAUNCH_PAD,
    ASCENT,
    APOGEE,
    DESCENT,
    PROBE_RELEASE,
    PAYLOAD_RELEASE,
    LANDED
} SoftwareState;

//returning the state in string literal
const char* getState(SoftwareState state)
{
    switch(state)
    {
        case LAUNCH_PAD: return "LAUNCH_PAD";
        case ASCENT: return "ASCENT";
        case APOGEE: return "APOGEE";
        case DESCENT: return "DESCENT";
        case PROBE_RELEASE: return "PROBE_RELEASE";
        case PAYLOAD_RELEASE: return "PAYLOAD_RELEASE";
        case LANDED: return "LANDED";
        default: return "N/A";
    }
}

int main()
{
    int i;
    float pressure0 = 101325.0;
    float apogee = 0.0;
    float prevAlt = 0.0;
    float currAlt = 0.0;
    float velocity = 0.0;
    
    //Dummy pressure data of 20 packets
    float pressure[] = { 101325.00, 101312.99, 101252.95, 100905.31, 100248.64,
                        98357.97,  96611.80,  94772.41,  93015.27,  92964.85,
                        93239.63,  94663.23,  95461.69,  96265.59,  97539.94,
                        99536.22, 100845.47, 101264.96, 101312.99, 101323.80};
                    
    SoftwareState state = LAUNCH_PAD;
                         
    for(i=1;i<=20;i++)
    {
        //calculating values
        currAlt = 44330 * (1 - (powf( pressure[i-1]/pressure0, 1/5.255) ) );
        velocity = currAlt-prevAlt;
        
        /* state transitioning
        not considering absolute values due to sensor readings error
        and mechanism lag */
        switch(state)
        {
            case LAUNCH_PAD: if(currAlt>5 && velocity>2)
                             state = ASCENT;
            break;
            case ASCENT: if(prevAlt>currAlt && velocity<5)
                        {
                            apogee = prevAlt;
                            state = APOGEE;
                        }
            break;
            case APOGEE: if(velocity<0 && prevAlt>currAlt)
                         state = DESCENT;
            break;
            case DESCENT: if(currAlt <= ((0.8*apogee)+2) )
                          state = PROBE_RELEASE;
            break;
            case PROBE_RELEASE: if(currAlt <= (2+2))
                                state = PAYLOAD_RELEASE;
            break;
            case PAYLOAD_RELEASE: if(fabs(velocity)<1 && currAlt<1)
                                  state = LANDED;
            break;
            case LANDED: break;
            default: printf("ERROR");
        }
        
        prevAlt=currAlt;
        
        //Printing Data
        printf("Packet:%d | Pressure:%.1f kPa | Altitude:%.1f m | Velocity:%.1f m/s | Apogee:%.1f m | State:%s\n", i,(pressure[i-1]/1000),currAlt,velocity,apogee,getState(state));
    }
    
    return 0;
    
}
