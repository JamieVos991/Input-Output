#include <pgmspace.h>
char index_html[] PROGMEM = R"=====(
<!doctype html>
<html lang='en' dir='ltr'>
<head>
  <meta http-equiv='Content-Type' content='text/html; charset=utf-8' />
  <meta name='viewport' content='width=device-width, initial-scale=1.0' />
  <title>Jamie's Ledstrip control</title>
  <script type='text/javascript' src='main.js'></script>

  <style>
    body {
      font-family:Arial,sans-serif;
      margin:10px;
      padding:0;
      background-color: grey;
      color:black;
      text-align:center;
    }

    .flex-row {
      display:flex;
      justify-content: center;
      flex-direction:row;
    }

    .flex-row-wrap {
      display:flex;
      flex-direction:row;
      justify-content: center;
      flex-wrap:wrap;
    }

    .flex-col {
      justify-content: center;
      display:flex;
      flex-direction:column;
      align-items:center;
    }

    ul {
      list-style-type: none;
    }

    ul li a {
      display:block;
      margin:3px;
      padding:10px;
      border:2px solid #404040;
      border-radius:5px;
      color: black;
      text-decoration:none;
    }

    ul#modes li a {
      min-width:220px;
    }

    ul.control li a {
      min-width:60px;
      min-height:24px;
    }

    ul.control {
      display:flex;
      flex-direction:row;
      justify-content: flex-end;
      align-items: center;
      padding: 0px;
    }

    ul li a.active {
      border:2px solid #909090;
    }
  </style>
</head>
<body>
  <div class='flex-row'>

    <div class='flex-col'>
      <div><canvas id='color-canvas' width='360' height='360'></canvas><br/></div>
      <div><input type='text' id='color-value' oninput='onColor(event, this.value)'/></div>

      </div>
    </div>

    <div>
      <ul id='modes' class='flex-row-wrap'>
    </div>
  </div>
</body>
</html>
)=====";
