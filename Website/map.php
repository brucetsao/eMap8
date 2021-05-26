<?php 
include("./Connections/map8key.php");
?>
	
<?php

   	include("./Connections/iotcnn.php");		//使用資料庫的呼叫程式
	
	$link=Connection();		//產生mySQL連線物件

   
?>
<!DOCTYPE html>
<html>
  <head>
    <style>
       /* Set the size of the div element that contains the map */

      html, body {
        margin: 0;
        padding: 0;
        height: 100%;
        width: 100%;
      }
      #map {
        height: 800px;  /* The height is 400 pixels */
        width: 100%;  /* The width is the width of the web page */
       }
      #map a.gomp-ctrl-logo {
          background-size: cover;
          height: 12px;
          width: 48px;
      }
	  #legend {
        font-family: Arial, sans-serif;
        background: #fff;
        padding: 10px;
        margin: 10px;
        border: 3px solid #000;
      }
      #legend h3 {
        margin-top: 0;
      }
      #legend img {
        vertical-align: middle;
      }
    </style>

	 <title>Taiwan Weather from Central Weather Bureau based on Open Weather Data Website </title>        

    <link rel="stylesheet" href="https://api.map8.zone/css/gomp.css?key=<?php echo $map8key; ?>" />
	
  </head>
    <?php
	include './title.php';
	?>


    <div align="center">
    <label><input type="radio" name="cwb" value="rain" checked checked>雨量</label>
    <label><input type="radio" name="cwb" value="temp">溫度</label>
    <label><input type="radio" name="cwb" value="humid">濕度</label>
    <label><input type="radio" name="cwb" value="bar">氣壓</label>
    </div>
    <div id="map" class="gomp-map"> </div>

<?php  include("./iotmap.php");?> 

<?php
include './footer.php';
?>
</body>
</html>
<?php


mysql_free_result($Recordset1);

?>
