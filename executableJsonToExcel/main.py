import json
import pandas as pd
import sys
import os
import glob
import ctypes  # An included library with Python install.
# import psutil

from os import listdir
from os.path import isfile, join
from datetime import datetime

onlyfiles = [f for f in listdir(sys.argv[1]) if isfile(join(sys.argv[1], f))]

jsonList = []

for x in onlyfiles:
    with open(sys.argv[1] + x) as json_file:
        data = json.load(json_file)
        jsonList.append(data)
        json_file.close()
dfRes = pd.json_normalize(jsonList)

now = datetime.now()
dt_string = 'Excel_data_JSON_railnova_' + now.strftime("%d-%m-%Y_%H-%M-%S")

dfRes.to_excel(sys.argv[2] + dt_string + '.xlsx')

files = glob.glob(sys.argv[1] + "/*")
for f in files:
    os.remove(f)

ctypes.windll.user32.MessageBoxW(0, "Les données JSON ont fini d'être traitée", "Traitement réussie")
sys.exit(0)