const searchInput = document.getElementById("searchInput");
const menuCards = document.querySelectorAll(".menu-card");

searchInput.addEventListener("input", function(){
    const searchText = searchInput.value.toLowerCase().trim();

    menuCards.forEach(function(card){
        const itemName = card.dataset.name.toLowerCase();

        if(itemName.includes(searchText)){
            card.style.display = "block";
        }
        else{
            card.style.display = "none";
        }
    });
});

const categoryButtons = document.querySelectorAll(".category");

categoryButtons.forEach(function(button){
    button.addEventListener("click", function(){
        const selectedCategory = button.dataset.category;

        categoryButtons.forEach(function(categoryButton){
            categoryButton.classList.remove("active");
        });
        button.classList.add("active");

        if(selectedCategory === "all"){
            menuCards.forEach(function(card){
                card.style.display = "block";
            });
        }

        else{

            menuCards.forEach(function(card){
                if(card.dataset.category === selectedCategory){
                    card.style.display = "block";
                }
                else{
                    card.style.display = "none";
                }
            });
        }

    });
});