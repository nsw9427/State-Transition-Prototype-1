const imagePopup = document.getElementById("imagePopup");
const imageBoxes = document.querySelectorAll(".image-box");
const closeButton = document.getElementById("closePopup");
const popupImage =  document.getElementById("popupImage");

imageBoxes.forEach(function(imageBox){
    imageBox.addEventListener("click",function(){
        const clickedImage = imageBox.querySelector("img");

        popupImage.src = clickedImage.src;
        popupImage.alt = clickedImage.alt;
        imagePopup.classList.add("open");
    });
});

closeButton.addEventListener("click",function(){
    imagePopup.classList.remove("open");
});