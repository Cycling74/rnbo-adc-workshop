# rnbo-web-app

This example showes how to use RNBO in a custom web app.

## Requirements

You're going to need node + npm for this one. As usual, I recommend 
installing these using nvm.

## Running the final output

If you want to skip ahead and just see the thing working, simply:

```
npx http-server
```

from this directory. The page should be visible at localhost:8080 or localhost:8081, check the terimal output to see which one.

## Directions

As usual, the `src` directory contains the final version of all modified source
files. So, if you get stuck, you can try to work towards those.

1. Start by cloning the repository at https://github.com/Cycling74/rnbo.example.webpage
2. For this example, I want us to combine RNBO with some kind of web radio
experiment. To be totally honest, I'm not sure what it's supposed to be. But
let's try it.
3. Start by going into `app.js` and deleting everything not related to the main
function or `makeSliders`.
4. Do the same in `index.html`. Just leave the section for the sliders.
5. Now go to this radio station and choose whatever radio station you like. 
6. Add an `audio` element to `index.html` with the URI of your radio station
as a `src`. Use `npx http-server` to serve your page locally, and make
sure that you can listen to the radio station.
7. Now, let's make a RNBO patch. Let's start with something very, very simple,
maybe a mono patch that just does some amplitude modulation on the input signal.
8. Make a web audio node for the `audio` element.

```js
const inputNode = new MediaElementAudioSourceNode(context, {
    mediaElement: document.getElementById("radio"),
    channelCount: 1
});
```

Connect it to the audio node from RNBO.

```js
inputNode.connect(device.node);
device.node.connect(outputNode);
```

9. Now you should be able to hear your internet radio station running through RNBO.
10. Let's make a more complex RNBO patch, maybe based around the `granulator~`
object. You can use `data` to hold on to your audio data, `splat~` to manage recording,
and `granulator~` to do all the fancy stuff. And you can use `param` objects to control
all of the inputs and outputs of your `granulator~` object.
11. One last fun thing that we can try would be to do some kind of visualization. I
don't really know what the `hilbert~` object does, but it could be something fun
to experiment with. If you look in the help file, you can see that it's got a 
2D visualizer with the first and second output. So let's replicate that.
12. Create a `hilbert~` object and connect it to two new outputs.
13. After you export the patch again, let's create a splitter and use it to
create our drawing code.

```js
const splitter = context.createChannelSplitter(3);

// Connect the device to the web audio graph
inputNode.connect(device.node);
device.node.connect(splitter);
splitter.connect(outputNode, 0, 0);
splitter.connect(analyzerNodeLeft, 1, 0);
splitter.connect(analyzerNodeRight, 2, 0);
```

And the drawing code
```js
function draw() {
    requestAnimationFrame(draw);

    const canvas = document.getElementById("canvas");
    const ctx = canvas.getContext("2d");
    let lastPoint;

    ctx.globalAlpha = 0.5;
    ctx.drawImage(canvas, -2, -2, canvas.width + 4, canvas.height + 4);
    // ctx.clearRect(0, 0, canvas.width, canvas.height);
    ctx.globalAlpha = 1.0;
    ctx.lineWidth = 3.0;

    if (analyzerNodeLeft && analyzerNodeRight) {
        analyzerNodeLeft.getFloatTimeDomainData(dataArrayLeft);
        analyzerNodeRight.getFloatTimeDomainData(dataArrayRight);

        
        for (let i = 0; i < 1024; i++) {
            const x = (dataArrayLeft[i] / 2 + 0.5) * canvas.width;
            const y = (dataArrayRight[i] / 2 + 0.5) * canvas.height;
            
            if (i === 0) {
            } else {
                ctx.strokeStyle = `hsl(${ i * 360 / 1024}deg 100% 50%)`;
                ctx.stroke
                ctx.beginPath();
                ctx.moveTo(lastPoint.x, lastPoint.y);
                ctx.lineTo(x, y);
                ctx.stroke();
            }
            
            lastPoint = {x, y};
        }

    }
}
```