## Compression Algorithms Comparison for Games & Game Assets

Games typcially pack their data into archives for easier redistribution and for space-constraints. I wanted to explore the two most ubiquitous compression methods for there suitability in game engines and which one would perform better in a realtime game application. The main factors being decompression speed and compressed size.

### ZIP
Zip is an archiving format, that is lossless and that can host a data-structure. Although this expirement is not interested in hosting filestructures itself, this might be something you would want in your game.

the implementation I based my expirements on is called [miniz](https://github.com/richgel999/miniz). I initially planned to use "[zip](https://github.com/kuba--/zip)", but it was not usable for fair benchmarking, I however found that zip is based on miniz.

### LZMA
Lzma unlike zip can not host a data-structure, for that reason it is often paired with [tar](https://en.wikipedia.org/wiki/Tar_(computing)). the implementation I have chosen for lzma is xz-utils aka [liblzma](https://tukaani.org/xz/) which is loosely based on the original implementation for 7zip

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
To be perferctly honest, I have been using the excellent software 7zip for a few years now. As such I was not completely unbiased when creating these test, expecting 7z to be superior in all categories. However, the results speak for themselves.


### The Results

#### 780kb

> Zip compression & decompression time

![780kb-zip-ct][780kb/zip-780-ct.png]