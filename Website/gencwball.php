<?php


$datastr1 =  "SELECT * FROM ncnuiot.cwbsite order by lat,lon ;"  ;	


$link1=Connection();	

				$resultzz1=mysql_query($datastr1,$link1);		
				$num_rows1 = mysql_num_rows($resultzz1);		
			echo "{\n\t\"type\": \"FeatureCollection\",\n\t\"features\": \n[";
			$count= 1 ;
	  if($num_rows1 >0)
		{
			while($row1 = mysql_fetch_array($resultzz1)) 
			{
				$tt = sprintf("\n{\n\t\"type\": \"Feature\",\n\t\"geometry\": {\n\t\t\"type\": \"Point\",\n\t\t\"coordinates\": [%f,%f]\n\t},\n\t\"properties\":\n\t{\n\t\t\"height\": %d ,\n\t\t\"wdir\": %d ,\n\t\t\"wspeed\": %d ,\n\t\t\"temp\": %f ,\n\t\t\"humid\": %f ,\n\t\t\"bar\": %f ,\n\t\t\"rain\": %f \n\t}\n}",$row1['lon'],$row1['lat'],$row1['height'],$row1['wdir'],$row1['wspeed'],$row1['temp'],$row1['humid'],$row1['bar'],$row1['rain']);

				echo $tt ;
				if ($count < $num_rows1)
					{
							$tmp = ",\n";
							echo $tmp ;
					}
				$count= $count +1	; 
			//	echo "<br>" ;		
			}
			// write tailer
			echo "\n\t]\n}";
			
			 mysql_free_result($resultzz1);
		}						

?>