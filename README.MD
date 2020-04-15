## Compression Algorithms Comparison for Games & Game Assets

Games typcially pack their data into archives for easier redistribution and for space-constraints. I wanted to explore the two most ubiquitous compression methods for there suitability in game engines and which one would perform better in a realtime game application.

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
