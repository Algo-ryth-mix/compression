from os import listdir
from os.path import isfile, join, abspath, dirname
import re as regex

here = dirname(abspath(__file__))
onlyfiles = [f for f in listdir(here) if isfile(join(here, f)) and f != __file__]

table = open("results.csv","w+")
table.write("sep=,\nDataSetName,Extreme,CompressTime,DecompressTime,CompressionRatio\n")


for file in onlyfiles:
    match = regex.search("^result([0-9]+).+$",file)
    if(match):
        dataset = match[1]
        extreme = False
        if((int(dataset) -1) % 2 == 0):
            print(f"extremeds: {dataset}")
            extreme = True

        with open(file,"r") as reader:
            content = [x.strip() for x in reader]
            if len(content) == 3:
                compresstime = content[0]
                decompresstime = content[1]
                compressratio = content[2]

                table.write(f"{dataset},{extreme},{compresstime},{decompresstime},{compressratio}\n")


