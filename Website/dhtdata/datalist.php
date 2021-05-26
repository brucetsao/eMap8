
<?php
 
   	include("../comlib.php");		//使用資料庫的呼叫程式
   	include("../Connections/iotcnn.php");		//使用資料庫的呼叫程式
		//	Connection() ;
  	$link=Connection();		//產生mySQL連線物件



	$qrystr="select a.*, b.*, c.* , a.id as mainid from ncnuiot.sitelist as a, ncnuiot.site as b, ncnuiot.sensortype as c where a.sensortype = c.sid and a.Did = b.id and a.sensortype = '01' order by b.siteid asc , a.mac asc limit 0,120 " ;		//將dhtdata的資料找出來

	$d00 = array();		// declare blank array of d00
	$d01 = array();	// declare blank array of d01
	$d02 = array();	// declare blank array of d02
	$d03 = array();	// declare blank array of d03
	$d04 = array();	// declare blank array of d04
	$d05 = array();	// declare blank array of d05
	$d06 = array();	// declare blank array of d06
	
	$result=mysql_query($qrystr,$link);		//將dhtdata的資料找出來(只找最後5

  if($result!==FALSE){
	 while($row = mysql_fetch_array($result)) 
	 {
			array_push($d00, $row["mainid"]);		// $row[欄位名稱] 就可以取出該欄位資料
			array_push($d01, $row["siteid"]);	// array_push(某個陣列名稱,加入的陣列的內容
			array_push($d02, $row["sitename"]);
			array_push($d03, $row["address"]);
			array_push($d04, $row["mac"]);
			array_push($d05, $row["longitude"]);
			array_push($d06, $row["latitude"]);
		}// 會跳下一列資料

  }
			
	
	 mysql_free_result($result);	// 關閉資料集
 
	 mysql_close($link);		// 關閉連線





?>


<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Frameset//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-frameset.dtd">
<html xmlns="http://www.w3.org/1999/xhtml">
<head>
<meta http-equiv="Content-Type" content="text/html; charset=utf-8" />
<title>Temperature and Humidity Device(Modbus) List</title>
<link href="webcss.css" rel="stylesheet" type="text/css" />

</head>
<body>
<?php
include '../title.php';
?>
<input type ="button" onclick="history.back()" value="BACK(回到上一頁)">
</input>
  <div align="center">
   <table border="1" align = center cellspacing="1" cellpadding="1">		
		<tr>
			<td>Site ID(站台編號)</td>
			<td>Site Name(站台名稱)</td>
			<td>Site Address(站台地址)</td>
			<td>MAC Adress(網路卡號)</td>
			<td>GPS</td>
			<td><a href='devicelistadd.php'>Manage(管理)</a>/Chart Display(圖表顯示)</td>
			</tr>

      <?php 
		  if(count($d00) >0)
		  {
				for($i=count($d00)-1;$i >=0  ;$i=$i-1)
					{
						echo sprintf("<tr><td>%s</td><td>%s</td><td>%s</td><td>%s</td><td>( %s , %s )</td><td><a href='devicelistadd.php'>Device Belong(裝置歸屬)/</a><a href='ShowChartlist.php?mac=%s'>Curve Chart</a>/<a href='ShowSingleGuage.php?mac=%s'>Guage Display</a></td></tr>", $d01[$i], $d02[$i], $d03[$i], $d04[$i], $d05[$i], $d06[$i], $d04[$i], $d04[$i]);
					 }
		 }
      ?>

   </table>

</div>

</form>
<?php
include '../footer.php';
?>

</body>
</html>
