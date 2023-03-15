let date = document.getElementById("current-date")
let time = document.getElementById("current-time")


setInterval(() =>{
    let d = new Date();
    date.innerHTML =d.toLocaleDateString();
},1000)

setInterval(() =>{
    let c = new Date();
    date.innerHTML =c.toLocaleTimeString();
},1000)




