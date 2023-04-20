let date = document.getElementById("current-date")
let time = document.getElementById("current-time")

let today = new Date();
let hour = today.getHours();

setInterval(() =>{
    let d = new Date();
    date.innerHTML =d.toLocaleDateString();
},1000)

setInterval(() =>{
    let c = new Date();
    time.innerHTML =c.toLocaleTimeString();
},1000)

let weatherDegrees = document.getElementById("js--weather-degrees");
let weatherMinDegrees = document.getElementById("js--weather-minDegrees");
let weatherMaxDegrees = document.getElementById("js--weather-maxDegrees");
let weatherHumidity = document.getElementById("js--weather-humidity");
let weatherPrecipitation = document.getElementById("js--weather-precipitation");

let currentWeather = fetch("https://api.open-meteo.com/v1/forecast?latitude=52.37&longitude=4.89&hourly=temperature_2m&hourly=relativehumidity_2m&daily=temperature_2m_max,temperature_2m_min,sunrise,sunset,precipitation_probability_max&forecast_days=1&timezone=auto")
    .then(function(response){
        return response.json();
    })
    .then(function(realData){
        weatherDegrees.innerHTML = realData.hourly.temperature_2m[hour];
        weatherMinDegrees.innerHTML = realData.daily.temperature_2m_min;
        weatherMaxDegrees.innerHTML = realData.daily.temperature_2m_max;
        weatherHumidity.innerHTML = realData.hourly.relativehumidity_2m[hour];
        weatherPrecipitation.innerHTML = realData.daily.precipitation_probability_max;
    });

let brigthnessIntensity = document.getElementById("js--brightness-intensity");
let brightness = document.getElementById("js--brightness");
let temperatureInside = document.getElementById("js--temperature-inside");
let temperatureOutside = document.getElementById("js--temperature-outside");
let currentBrightness = fetch("https://35829.hosts2.ma-cloud.nl/IoT/post.php")
    .then(function(response){
        return response.json();
    })
    .then(function(realData){
        if(realData.licht < 200){
            brigthnessIntensity.innerHTML = "Low";
        }
        else if(realData.licht < 500){
            brigthnessIntensity.innerHTML = "Medium";
        }
        else if(realData.licht < 800){
            brigthnessIntensity.innerHTML = "High";
        }
        brightness.innerHTML = realData.licht;
        temperatureInside.innerHTML = Number((realData.temp).toFixed(1));
        temperatureOutside.innerHTML = Number((realData.temp).toFixed(1));
        //de temp is hetzelfde vanwege dat er maar 1 sensor is aaangeboden
    })
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


const labels = [
    "Water",
    "Gas",
    "Electricity",
];
    
const data1 = {
    labels: labels,
    datasets:[
        {
            label: "Gas, Water en Electricity Usage",
            data: [1500, 2000, 1000],
            borderColor: '#fff',
            backgroundColor: ['#438b59', '#336843', '#275234'],
            borderWidth: 2
        }
    ]
};
    
const config = {
    type: 'bar',
    data: data1,
};
    
const chart1 = new Chart(document.getElementById("js--chart-1"), config);