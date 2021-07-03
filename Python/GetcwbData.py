import sys
import requests
import json
import time
import datetime
import math
import os
import http.client
import unicodedata
from pathlib import Path

from requests.exceptions import HTTPError
str1=""
str2=""



url='https://opendata.cwb.gov.tw/api/v1/rest/datastore/O-A0001-001?Authorization=CWB-8D336EBD-4CD8-4077-AD00-F5551E8DE2DA&format=JSON'
try:
    res = requests.get(url)
    res.raise_for_status()
except HTTPError as http_err:
    print('HTTP error occurred: {http_err}')
    sys.exit(0)
except Exception as err:
    print('Other error occurred: {err}')
    sys.exit(0)
else:
    print('Success!')
table=json.loads(res.content.decode('utf-8'))
print('return value = %s' %table['success'])

for data in table['records']['location']:
    print('item name =%s' % data['stationId'])
    print('item name =%s' % data['locationName'])
    s01 = data['stationId']
    s02 = data['locationName']
    s03 = data['time']['obsTime']
    s04 = data['lat']
    s05 = data['lon']
    data2 = data['weatherElement']
    s06 = data2[0]['elementValue']
    s07 = data2[1]['elementValue']
    s08 = data2[2]['elementValue']
    s09 = data2[3]['elementValue']
    s10a = data2[4]['elementValue']
    s10 = float(s10a)*10
    s11 = data2[5]['elementValue']
    s12 = data2[6]['elementValue']
    data3 = data['parameter']
    s13 = data3[1]['parameterValue']
    s14 = data3[0]['parameterValue']
    s15 = data3[3]['parameterValue']
    s16 = data3[2]['parameterValue']
    str1 = "http://163.22.24.51:9999"
    str2 = "/opendata/rainadd.php?f01=\'%s\'&f02=\'%s\'&f03=\'%s\'&f04=%s&f05=%s&f06=%s&f07=%s&f08=%s&f09=%s&f10=%s&f11=%s&f12=%s&f13=\'%s\'&f14=\'%s\'&f15=\'%s\'&f16=\'%s\'" %(s01, s02, s03, s04, s05, s06, s07, s08, s09, s10, s11, s12, s13, s14, s15, s16)
    str = str1+str2
    print(str)


    try:
        x = requests.get(str)
        print(x.status_code)
    except: # request.exceptions.RequestException as e: #requests.exceptions.RequestException as e:
        print('Exception in data_output')
