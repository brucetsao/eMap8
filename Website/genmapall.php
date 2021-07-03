<?php

	
$str1 =  "select * from ncnuiot.site order by 	latitude,longitude	 ;"  ;	

				$result1=mysql_query($str1,$link);		
				$num_rows = mysql_num_rows($result1);		
			echo "{\n\t\"type\": \"FeatureCollection\",\n\t\"features\": \n[";
			$count= 1 ;		
			$tt = "" ;
				while($row = mysql_fetch_array($result1)) 	
					{	
						$tt = sprintf("\"title\": \"%s <br> (%s) <br> GPS:(%s,%s) <br> %s <br>",$row['sitename'],$row['siteid'],$row['longitude'],$row['latitude'],$row['address']);		
						$str2 =  sprintf("select * from ncnuiot.sitelist, ncnuiot.sensortype where sensortype.sid = sitelist.sensortype and sitelist.Did = %d order by sensortype asc ",$row['id'] );
						$result2=mysql_query($str2,$link);	
						while($row2 = mysql_fetch_array($result2)) 	
						{	
							$mac = $row2['mac'] ;
							$sensortp = $row2['sensortype'] ;
							if (!strcmp($sensortp, "01"))
									{
										$str3 =  sprintf("select * from ncnuiot.dhtData where MAC = '%s' order by systime desc limit 0,1 ",$mac );	
										$result3=mysql_query($str3,$link);	
											while($row3 = mysql_fetch_array($result3)) 
											{
					//							echo sprintf("Sensor:%s Temperature:%f ,Humidity: %f <br>",$row2['ename'],$row3['temperature'],$row3['humidity'])."<br>";
												$tt = $tt.sprintf("location:%s Sensor:%s Temperature(%f) ,Humidity(%f)<br>",$row2['ps'],$row2['ename'],$row3['temperature'],$row3['humidity']);
											}
									}	//   end of if ($sensortp == 
								
							if (!strcmp($sensortp, "11"))
									{
										//select *  from ncnuiot.dhtData where MAC = '246F28248CE0' order by systime desc  limit 0,1
										$str3 =  sprintf("select * from ncnuiot.dht where MAC = '%s' order by systime desc limit 0,1 ",$mac );	
										$result3=mysql_query($str3,$link);	
											while($row3 = mysql_fetch_array($result3)) 
											{
												$tt = $tt.sprintf("location:%s Sensor:%s Temperature(%f) ,Humidity(%f)<br>",$row2['ps'],$row2['ename'],$row3['temperature'],$row3['humidity']);
											}
									}	//   end of if ($sensortp == 
								
							if (!strcmp($sensortp, "12"))
									{
										//select *  from ncnuiot.dhtData where MAC = '246F28248CE0' order by systime desc  limit 0,1
										$str3 =  sprintf("select * from ncnuiot.lux where MAC = '%s' order by systime desc limit 0,1 ",$mac );	
										$result3=mysql_query($str3,$link);	
											while($row3 = mysql_fetch_array($result3)) 
											{
												$tt = $tt.sprintf("location:%s Sensor:%s Lux Value(%f) <br>",$row2['ps'],$row2['ename'],$row3['luxvalue']);
											}
									}	//   end of if ($sensortp == 
								
								// 41 is dhtData
							if (!strcmp($sensortp, "41"))
									{
										//select *  from ncnuiot.dhtData where MAC = '246F28248CE0' order by systime desc  limit 0,1
										$str3 =  sprintf("select * from ncnuiot.noise where MAC = '%s' order by systime desc limit 0,1 ",$mac );	
										$result3=mysql_query($str3,$link);	
											while($row3 = mysql_fetch_array($result3)) 
											{
												$tt = $tt.sprintf("location:%s Sensor:%s Decibel Value(%f)<br>",$row2['ps'],$row2['ename'],$row3['dbvalue']);
											}
									}	//   end of if ($sensortp == 
								
								// 64 is mq3
							if (!strcmp($sensortp, "63"))
									{
										//select *  from ncnuiot.dhtData where MAC = '246F28248CE0' order by systime desc  limit 0,1
										$str3 =  sprintf("select * from ncnuiot.mq4 where MAC = '%s' order by systime desc limit 0,1 ",$mac );	
//										echo $str3."<br>";
										$result3=mysql_query($str3,$link);	
											while($row3 = mysql_fetch_array($result3)) 
											{
												$tt = $tt.sprintf("location:%s Sensor:%s Methane Gas(%f)<br>",$row2['ps'],$row2['ename'],$row3['mqvalue']);
											}
									}	//   end of if ($sensortp == 
							if (!strcmp($sensortp, "64"))
									{
										//select *  from ncnuiot.dhtData where MAC = '246F28248CE0' order by systime desc  limit 0,1
										$str3 =  sprintf("select * from ncnuiot.mq7 where MAC = '%s' order by systime desc limit 0,1 ",$mac );	
										$result3=mysql_query($str3,$link);	
											while($row3 = mysql_fetch_array($result3)) 
											{
												$tt = $tt.sprintf("location:%s Sensor:%s Carbon Monoxide(%f)<br>",$row2['ps'],$row2['ename'],$row3['mqvalue']);
											}
									}	//   end of if ($sensortp == 
								
						
						}		// end of while($row2 = mysql_fetch_array($result2)) 	
					$tt = $tt."\"" ;
				$tmp = sprintf("\n\t{\n\t\t\"type\": \"Feature\",\n\t\t\"properties\": {\n\t\t\t\"amount\": %d ,\n\t\t\t %s ,\n\t\t\t\"species\": \"%s\"},\n\t\t\"geometry\": {\n\t\t\t\"type\": \"Point\",\n\t\t\t\"coordinates\": [%f, %f]\n\t\t}\n\t}",$row['id'],$tt,'Environement',$row['longitude'],$row['latitude']);

				echo $tmp ;

				if ($count < $num_rows)
					{
							$tmp = ",\n";
							echo $tmp ;
					}
				$count= $count +1	; 
			}	// end of while($row = mysql_fetch_array($result1)) 	 ALL data is here
			echo "\n\t]\n}";
			
			 mysql_free_result($result1);
			 mysql_free_result($result2);
			 mysql_free_result($result3);
	 			 			 

?>