let date = document.getElementById("current-date")
let time = document.getElementById("current-time")


setInterval(() =>{
    let d = new Date();
    date.innerHTML =d.toLocaleDateString();
},1000)

setInterval(() =>{
    let c = new Date();
    time.innerHTML =c.toLocaleTimeString();
},1000)

let weatherDegrees = document.getElementById("js--weather-degrees");
console.log(weatherDegrees);


const sunrise = document.getElementById("js--sunrise");
const sunset = document.getElementById("js--sunset");

let data = fetch("https://api.open-meteo.com/v1/forecast?latitude=52.37&longitude=4.89&hourly=temperature_2m&daily=temperature_2m_max,temperature_2m_min,sunrise,sunset,precipitation_sum&forecast_days=1&timezone=auto")
.then(function(response){
        return response.json();
    }).then(
        function(realData){
            const sunriseTime = new Date(realData.daily.sunrise).toLocaleTimeString([], {hour: '2-digit', minute:'2-digit'});
            const sunsetTime = new Date(realData.daily.sunset).toLocaleTimeString([], {hour: '2-digit', minute:'2-digit'});
            sunrise.innerHTML = sunriseTime;
            sunset.innerHTML = sunsetTime;
        }
    );