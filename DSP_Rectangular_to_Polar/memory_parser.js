const fs = require('fs');



function testTwoHex(x) {
    if(x.length !== 2) return false;
    let table = ["A", "B", "C", "D", "E", "F", "0", "1", "2", "3", "4", "5", "6", "7", "8", "9"];
    return table.includes(x[0]) && table.includes(x[1])
}

function IEEE754_to_float(s) {
    let buffer = new ArrayBuffer(4);
    let bytes = new Uint8Array(buffer);
    bytes[0] = parseInt(`${s[0]}${s[1]}`, 16);
    bytes[1] = parseInt(`${s[2]}${s[3]}`, 16);
    bytes[2] = parseInt(`${s[4]}${s[5]}`, 16);
    bytes[3] = parseInt(`${s[6]}${s[7]}`, 16);     
    let view = new DataView(buffer);
    // If you only had a Uint8Array, you would use bytes.buffer instead of buffer.
    // console.log(view.getFloat32(0, false));
    return view.getFloat32(0, false);
}

fs.readFile('sinwave_mem_dump.txt', "utf8", function(err, data) {
    // console.log(data.split(' '));
    let byte_ary = data.split(' ').filter((e) => testTwoHex(e));
    // console.log(byte_ary)
 
    let numbers = [];
    
    let cnt = 0;
    for(let i = 0; i < byte_ary.length; i++) {
        if(i % 4 === 0) {
            numbers.push(`${byte_ary[i + 3]}${byte_ary[i + 2]}${byte_ary[i + 1]}${byte_ary[i]}`);
        }
    }

    let outputDoc = '';
    // console.log(numbers.map(e => IEEE754_to_float(e)));
    let outputAry = numbers.map(e => IEEE754_to_float(e));
    for(let i = 0; i < outputAry.length; i++) {
        outputDoc += `${outputAry[i]}\n`;
    }
    // console.log(numbers.length);
    console.log(outputDoc);
});


/*
online tool using

https://c3js.org/samples/simple_xy.html

1. Image to teach user dump log file https://tinyurl.com/y4y7lcjl

Input dump.txt

0x200004CC  00 00 00 00 D9 AB 17 3F - 15 04 C2 BD 15 EF 43 3E .......?......C>
0x200004DC  00 00 80 3F 09 B8 D5 3E - F3 04 B5 3E 72 AD A0 3F ...?...>...>r..?
0x200004EC  D7 B3 5D 3F 5E 83 EC 3E - B2 E4 A8 3F 8D 65 97 3F ..]?^..>...?.e.?
0x200004FC  00 00 00 3F 8D 65 97 3F - B2 E4 A8 3F 5E 83 EC 3E ...?.e.?...?^..>
0x2000050C  D7 B3 5D 3F 72 AD A0 3F - F3 04 B5 3E 09 B8 D5 3E ..]?r..?...>...>
0x2000051C  00 00 80 3F 15 EF 43 3E - 15 04 C2 BD D9 AB 17 3F ...?..C>.......?
0x2000052C  00 00 00 80 D9 AB 17 BF - 15 04 C2 3D 15 EF 43 BE ...........=..C.
0x2000053C  00 00 80 BF 09 B8 D5 BE - F3 04 B5 BE 72 AD A0 BF ............r...
0x2000054C  D7 B3 5D BF 5E 83 EC BE - B2 E4 A8 BF 8D 65 97 BF ..].^........e..

2. 
plot `outputAry` with C3.js
*/
