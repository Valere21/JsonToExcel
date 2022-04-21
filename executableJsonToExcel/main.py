import json
import pandas as pd
import sys
from os import listdir
from os.path import isfile, join
from datetime import datetime
import os
import glob
import ctypes  # An included library with Python install.
from tkinter import messagebox

# messagebox.showinfo("Basic Example", "a Basic Tk MessageBox")

onlyfiles = [f for f in listdir(sys.argv[1]) if isfile(join(sys.argv[1], f))]
# onlyfiles = [f for f in listdir("C:/JSONbrut/ModifiedJSON") if isfile(join("C:/JSONbrut/ModifiedJSON", f))]
# print(onlyfiles)

jsonList = []

for x in onlyfiles:
    with open(sys.argv[1] + x) as json_file:
        data = json.load(json_file)
        jsonList.append(data)
        json_file.close()
dfRes = pd.json_normalize(jsonList)

now = datetime.now()
dt_string = 'Excel_data_JSON_railnova_' + now.strftime("%d-%m-%Y_%H-%M-%S")

# p = psutil.Process(sys.argv[3])
# p.terminate()  #or p.kill()

dfRes.to_excel(sys.argv[2] + dt_string + '.xlsx')

files = glob.glob(sys.argv[1] + "/*")
for f in files:
    os.remove(f)

# p = psutil.Process(sys.argv[3])
# p.kill()  #or p.kill()

# os.kill(sys.argv[3], signal.SIGTERM)  # or signal.SIGKILL

ctypes.windll.user32.MessageBoxW(0, "Les données JSON ont fini d'être traitée", "Traitement réussie")
