//includes of needed libraries
const download = require("image-download");
const fs = require("fs");
const R = require("ramda");
const terminal = require("terminal-image");

//create the array of items
const flickrImageData = R.compose(
    R.prop('items'),
  );


    //determine the media from the list, if the user selects somthing out side of 0-19, just select 0
  const uLink = pic=>R.compose(
    R.and(pic<=19,pic>=0)?R.nth(pic):R.head(),
    R.map(R.prop('m')),
    R.map(R.prop('media')),
    flickrImageData,
  );

download(
    //download the link using the ulink with second user argument, parsing the dogs.JSON file,         
    uLink( process.argv[2]) (JSON.parse(fs.readFileSync('dogs.json', 'utf8'))) ).then 
            (buf=>
                //then buffer the user input using promises, and log the buffered output, otherwise catch a 404 
                {terminal.buffer(buf).then
                    (
                        prom=>{console.log(prom);}
                    )
                }
            ).catch
                (error=>{console.log("image not found")}
        );
