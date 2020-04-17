## Compression Algorithms Comparison for Games & Game Assets

### Justification

Games typcially pack their data into archives for easier redistribution and for space-constraints. I wanted to explore the two most ubiquitous compression methods for there suitability in game engines and which one would perform better in a realtime game application. The main factors being decompression speed and compressed size.

### ZIP
ZIP is an archiving format, that is lossless and that can host a data-structure. Although this expirement is not interested in hosting filestructures itself, this might be something you would want in your game.

the implementation I based my expirements on is called [miniz](https://github.com/richgel999/miniz). I initially planned to use "[ZIP](https://github.com/kuba--/ZIP)", but it was not usable for fair benchmarking, I however found that ZIP is based on miniz.

### LZMA
LZMA unlike ZIP can not host a data-structure, for that reason it is often paired with [tar](https://en.wikipedia.org/wiki/Tar_(computing)). the implementation I have chosen for LZMA is xz-utils aka [libLZMA](https://tukaani.org/xz/) which is loosely based on the original implementation for 7ZIP

### The Test

The test I created consist fundamentally of 3 parts

 - The Benchmark
 - The Adapter
 - and The Algorithm

a singular run looks something like this:
```cpp
//pseudocode

main(arguments) {
    auto dataset in arguments;
    auto level in arguments;

    for (_ in 0 to 10) {
        {
            compressor c with level;
            make_compression_benchmark();
            c.compress(dataset);
            end_benchmark();
        }
        {
            decompressor dc;
            make_decompression_benchmark();
            dc.decompress(dataset);
            end_benchmark();
        }
        {
            compare_datasets();
        }
    }

    average_results();
    write_results();
}
```

Feel free to look at the actual code included in this repository under src/

### The Datasets
I used my own datasets, which closely resemble things that are included in a game. for time-constraints I did not use data-sets bigger than 250.000kb as it would have taken excessively long to create all the results. The data I used where 212.631kb, 31.610kb, 6700kb and 780kb respectively. The only criteria I had for these Datasets where that they have been produced by me (to avoid licensing them) and that they included the typical assets a game would have (sprites,audio,code,binaries etc...), both algorithms performed on these two test, with all their available settings.


### My expectations
To be perferctly honest, I have been using the excellent software 7ZIP for a few years now. As such I was not completely unbiased when creating these test, expecting 7z to be superior in all categories. However, the results speak for themselves.


### The Results

#### 780kb

> ZIP compression & decompression time
>
>![780kb-zip-ct](780kb/zip-780-ct.png "780kb-zip-ct")

>LZMA compression & decompression time
>
>![780kb-lzma-ct](780kb/lzma-780-ct.png "780kb-lzma-ct")

Note LZMA has ranges 0-9 and an extreme switch, the results in green are the normal results,
from this we can already see that it takes an order of magnitude longer to compress than it takes to decompress, regardless of the alorithm. Furthermore ZIP scales way more dramatically than LZMA. However take a close look on the scales. LZMA is somewhere between 10x and 2x slower than ZIP. (The scale is a bit squished for decompression, but ZIP wins here as well)

The other main point is the compression ratio:
aka compressed-size/raw-size

> ZIP compression ratios
>
>![780kb-zip-cr](780kb/zip-780-cr.png "780kb-zip-cr")

>LZMA compression ratios
>
>![780kb-lzma-cr](780kb/lzma-780-cr.png "780kb-lzma-cr")

As you can see from this example, both of them seem to struggle when it comes to scaling, from ZIP you get deminshing returns after preset 3 and LZMA really only seems to perform in "Extreme" mode at all. Note however that LZMA has the leading edge here by at least 5%

More examples:

#### 6700kb
> ZIP compression & decompression time
>
>![6700kb-zip-ct](6700kb/zip-6700-ct.png "6700kb-zip-ct")

>LZMA compression & decompression time
>
>![6700kb-lzma-ct](6700kb/lzma-6700-ct.png "6700kb-lzma-ct")

> ZIP compression ratios
>
>![6700kb-zip-cr](6700kb/zip-6700-cr.png "6700kb-zip-cr")

>LZMA compression ratios
>
>![6700kb-lzma-cr](6700kb/lzma-6700-cr.png "6700kb-lzma-cr")

#### 31610kb
> ZIP compression & decompression time
>
>![31610kb-zip-ct](31610kb/zip-31610-ct.png "31610kb-zip-ct")

>LZMA compression & decompression time
>
>![31610kb-lzma-ct](31610kb/lzma-31610-ct.png "31610kb-lzma-ct")

> ZIP compression ratios
>
>![31610kb-zip-cr](31610kb/zip-31610-cr.png "31610kb-zip-cr")

>LZMA compression ratios
>
>![31610kb-lzma-cr](31610kb/lzma-31610-cr.png "31610kb-lzma-cr")

Note this is the first time that we can observe LZMA having different behaviour at lower levels at all, to me it is not entirely clear why, but it seems to oscillate between two different settings. Furthermore "extreme" was only able to beat the normal mode in the highest settings. LZMA still wins in terms of compressed size, and it not excessively slower in decompression than ZIP, however ZIP still wins in compression 
speed.

#### 212631kb
> ZIP compression & decompression time
>
>![212631kb-zip-ct](212631kb/zip-212631-ct.png "212631kb-zip-ct")

>LZMA compression & decompression time
>
>![212631kb-lzma-ct](212631kb/lzma-212631-ct.png "212631kb-lzma-ct")

> ZIP compression ratios
>
>![212631kb-zip-cr](212631kb/zip-212631-cr.png "212631kb-zip-cr")

>LZMA compression ratios
>
>![212631kb-lzma-cr](212631kb/lzma-212631-cr.png "212631kb-lzma-cr")

Note LZMA seemes to really benefit from "Ultra", wheras ZIP shows diminshing returns consistently after the 3rd preset.

### The conclusion

Which algorithm to choose ? preferentally both for different sections of your game. LZMA shines with overall smaller compressed archives and still quite good decompression speeds. However to store savegames, it is less than ideal. compressing big datasets in realtime is not feasable, and unless you can save your game asynchronously I would not recommend it.
ZIP on the other hand, has good compression and excellent decompression speeds while maintaining a respectable archive size. it is ideal for saving data your game produces. However if you absolutely must choose only one, use LZMA if you suspect that your save-games will stay small, as it does not take significantly more time to compress small data then ZIP, otherwise use ZIP. If you require a starting point for one or both algorithms feel free to use this repository as inspiration. Make sure to checkout [LICENSE.MD](LICENSE.MD) and [THIRD_PARTY_LICENSES.MD](THIRD_PARTY_LICENSES.MD) before however. (don't worry it is all very open.)

### Using this
Can I use this to compare my own datasets? Yes, here is how to do it.

#### step 0
- get cmake
- get python3
- get liblzma


#### step 1 Compiling

First. you need a windows host (sorry no linux support currently). then get precompiled binaries for liblzma or compile them yourself. (make sure you have the lib and the dll not just a [def and a dll](https://stackoverflow.com/questions/9360280/how-to-make-a-lib-file-when-have-a-dll-file-and-a-header-file)) place the lib alongside the main.cpp, place the dll in your cmake output path(where the binaries are going to be built).
Then adjust testing/autotest.bat for your own datasets. finally run bootstrap-test.bat in the root directory.

#### step 2 Using the datasets

the bootstrap-test.bat creates two directories for you, "results.zip" and "results.lzma", choose whatever one you want and copy all `.txt` files into the folder called "stitching". in that directory run `python3 data_stitcher.py`
this will create a results.csv file that you can open in your favourite spreadsheet programm

#### step 3 visualizing the data with excel

copy one of the spreadsheets from the xxxkb folder to a new folder, call it whatever you like, choose the spreadsheet that corresponds to the dataset you just stitched.
copy the results.csv to that folder as well. open both spreadsheets in excel. In the results.csv use the sort function of excel to sort the entire sheet using the "Extreme" row. Copy the diagrams over to the new spreadsheet (making sure to also copy the green bars). Now right click on the diagram and select set datasets, enter the new datasets from the results.csv, finally save the results.csv as \<yourcustomname\>.xlsx otherwise the diagrams will be gone. to export the diagrams, CTRL-C the diagram and CTRL-V it in Paint.

#### Extra time spent on this:
~ 20 hrs attempting to compiling lib7z, this library was dropped as it didn't work out for linux or mac, and the AES-Encryption in it was deemed as a CVE (CVE-2018-10172), although this repository doesn't use the encryption module at all and although 7z was fixed, I did not feel comfortable using this library anymore, this was replaced by the excellent xz-utils, which compiled for windows without much trouble.

~ 15 hrs of creating the initial adaptor, this was done before the repository was initialized, the first 3 commits show this change, this was not recorded as I initially created this within the liblzma repository for a quick test. but I liked the adaptor enough to go on with it into testing directly.

~ 7 hrs generating the datasets, these were then compiled into the graphs on this page.