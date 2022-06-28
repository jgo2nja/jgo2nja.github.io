function drop() {
  document.getElementById("menu").classList.toggle("show");
}

window.onclick = function(thing){
  if(!thing.target.matches('.pushDrop'){
     var options = document.getElementsByClassName("dropOptions");
     var iter;
     for (iter=0; iter < options.length; iter++){
       var openDrop = options[i];
       if(openDrop.classList.contains('show')){
         openDrop.classList.remove('show');
       }
     }
  }
}
