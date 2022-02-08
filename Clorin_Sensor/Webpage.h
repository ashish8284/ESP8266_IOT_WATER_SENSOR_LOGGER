String Gateway_Status = "Null" ;
String Residual_Chlorine = "Null" ;
String HypoClorous_acid = "Null" ;
String Electrode_Signal = "Null";
String Temperature = "Null";
String CL_IP = "Null";

AsyncWebServer server(80);
AsyncEventSource events("/events");

unsigned long lastTime = 0;
unsigned long timerDelay = 3000;  // send readings timer

String processor(const String& var) {
  if (var == "Gateway_Status") {
    return String(Gateway_Status);
  }
  if (var == "Residual_Chlorine") {
    return String(Residual_Chlorine);
  }
  if (var == "HypoClorous_acid") {
    return String(HypoClorous_acid);
  }
  else if (var == "Electrode_Signal") {
    return String(Electrode_Signal);
  }
  else if (var == "Temperature") {
    return String(Temperature);
  }
  else if (var == "CL_IP") {
    return String(CL_IP);
  }
}

const char index_html[] PROGMEM = R"rawliteral(
<!DOCTYPE HTML><html>
<head>
  <title>Techno Automation</title>
  <meta name="viewport" content="width=device-width, initial-scale=1">
  <link rel="stylesheet" href="https://use.fontawesome.com/releases/v5.7.2/css/all.css" integrity="sha384-fnmOCqbTlWIlj8LyTjo7mOUStjsKC4pOpQbqyi7RrhN7udi9RwhKkMHpvLbHG9Sr" crossorigin="anonymous">
  <link rel="icon" href="data:,">
  <style>
    html {font-family: Arial; display: inline-block; text-align: center;}
    p {  font-size: 1.5rem;}
    body {  margin: 0;}
    .topnav { overflow: hidden; background-color: #4B1D3F; color: white; font-size:1.5rem; }
    .content { padding: 10px; }
    .card { background-color: white; box-shadow: 2px 2px 12px 1px rgba(140,140,140,.5); }
    .cards { max-width: auto; margin: 0 auto; display: grid; grid-gap: 1rem; grid-template-columns: repeat(auto-fit, minmax(200px, 1fr)); }
    .reading { font-size: 2rem; }
    .card.Gateway_Status { color: #0b7c7b; }
    .card.Residual_Chlorine { color: #0e7c7b; }
    .card.HypoClorous_acid { color: #037c7b; }
    .card.Electrode_Signal { color: #3fca6b; }
    .card.Temperature { color: #d62246; }
    .card.CL_IP { color: ##bb10eb; }
  </style>
</head>
<body>
  <div class="topnav">
    <h4>Tech Clorin Sensor(TA)V1</h4>
  </div>
  <div class="content">
    <div class="cards">
      <div class="card Gateway_Status">
        <h4><i class="fas fa-compress"></i> Gateway_Status</h4><p><span class="reading"><span id="M_S1">%Gateway_Status%</span></span></p>
      </div>
      <div class="card Residual_Chlorine">
        <h4><i class="fas fa-tint"></i> Residual_Chlorine</h4><p><span class="reading"><span id="M_S2">%Residual_Chlorine%</span></span> mg/L</p>
      </div>
      <div class="card HypoClorous_acid">
        <h4><i class="fas fa-tint"></i> HypoClorous_acid</h4><p><span class="reading"><span id="M_S3">%HypoClorous_acid%</span></span> mg/L</p>
      </div>
      <div class="card Electrode_Signal">
        <h4><i class="fas fa-signal"></i> Electrode_Signal</h4><p><span class="reading"><span id="M_S4">%Electrode_Signal%</span></span> mV</p>
      </div>
      <div class="card Temperature">
        <h4><i class="fas fa-thermometer-full"></i> Temperature</h4><p><span class="reading"><span id="M_S5">%Temperature%</span></span> Deg.</p>
      </div>
      <div class="card CL_IP">
        <h4><i class="fa fa-link"></i> CL_IP</h4><p><span class="reading"><span id="IP">%CL_IP%</span></span></p>
      </div>
    </div>
  </div>
<script>
if (!!window.EventSource) {
 var source = new EventSource('/events');

 source.addEventListener('open', function(e) {
  console.log("Events Connected");
 }, false);

 source.addEventListener('Fault', function(e) {
  if (e.target.readyState != EventSource.OPEN) {
    console.log("Events Disconnected");
  }
 }, false);

 source.addEventListener('message', function(e) {
  console.log("message", e.data);
 }, false);

 source.addEventListener('Gateway_Status', function(e) {
  console.log("Gateway_Status", e.data);
  document.getElementById("M_S1").innerHTML = e.data;
 }, false);

 source.addEventListener('Residual_Chlorine', function(e) {
  console.log("Residual_Chlorine", e.data);
  document.getElementById("M_S2").innerHTML = e.data;
 }, false);

 source.addEventListener('HypoClorous_acid', function(e) {
  console.log("HypoClorous_acid", e.data);
  document.getElementById("M_S3").innerHTML = e.data;
 }, false);

 source.addEventListener('Electrode_Signal', function(e) {
  console.log("Electrode_Signal", e.data);
  document.getElementById("M_S4").innerHTML = e.data;
 }, false);

 source.addEventListener('Temperature', function(e) {
  console.log("Temperature", e.data);
  document.getElementById("M_S5").innerHTML = e.data;
 }, false);

  source.addEventListener('CL_IP', function(e) {
  console.log("CL_IP", e.data);
  document.getElementById("IP").innerHTML = e.data;
 }, false);

}
</script>
</body>
</html>)rawliteral";

void Webpabe_Update() {
  events.send("ping", NULL, millis());
  events.send(String(Gateway_Status).c_str(), "Gateway_Status", millis());
  events.send(String(Residual_Chlorine).c_str(), "Residual_Chlorine", millis());
  events.send(String(HypoClorous_acid).c_str(), "HypoClorous_acid", millis());
  events.send(String(Electrode_Signal).c_str(), "Electrode_Signal", millis());
  events.send(String(Temperature).c_str(), "Temperature", millis());
  CL_IP = WiFi.localIP().toString();
  events.send(String(CL_IP).c_str(), "CL_IP", millis());
  ArduinoOTA.handle();
}
