# rnbo-custom-vst

Here we're going to look at how to use RNBO to build a JUCE-based VST,
with a custom UI. We'll be looking specifically at how to create 
interface elements that bind to specific RNBO parameters, and how
to get and set parameters.

## Prerequisites

You're gonna need git.

## Directions

First thing to do is to clone the repo at github.com/cycling74/rnbo.example.juce.
This has the basic framework for building both a standalone JUCE app
as well as a plugin. It's also got a git submodule set up to handle downloading
JUCE as a git submodule. The important thing here though is that you can't just
download it as a zip, you actually have to clone the repo. The repo recommends
actually creating a new repo, using this one as a template. This isn't strictly
necessary, but you can't just download it as a .zip file because then you won't
have any access to submodules. 

Once you've got the repo cloned, you can get the JUCE submodule.

```
git submodule update --init --recursive --progress
```

Alright, now you're ready for the slightly annoying process needed in order to
use a custom UI. First, take the RNBO Intro patch and export it into the folder
called `export` in the JUCE template. You'll notice that this contains a folder
`rnbo/adapters/juce`. Important stuff is in here. This is basically the bridge 
between JUCE and your exported RNBO patch. In order to make a custom VST, we'll
be overwriting these files. 

1. Copy the file `export/rnbo/adapters/juce/RNBO_JuceAudioProcessor.h` and 
`export/rnbo/adapters/juce/RNBO_JuceAudioProcessor.cpp` to `src`. We're basically
going to leave this code totally untouched but for a couple of very small changes. 
There's a file in that same folder called
`export/rnbo/adapters/RNBO_JuceAudioProcessorEditor.cpp`, which implements the
actual editor. We're going to completely re-implement this file. The don't really
need to touch the audio processor itself, but for the fact that it implements a
function called `createEditor` that returns an instance of the editor that we
want to use. We need to override this function. Now, unfortunately, we can't just
subclass `RNBO_JuceAudioProcessor` with a new implementation of this function, 
because that file also provides an implementation for `createPluginFilter`, a
global function that provides the entry point into our plugin. In a very short 
amount of time, this will change for the better, but for this workshop the way
to implement your own UI is still to copy `RNBO_JuceAudioProcessor`, change the
implementation of `createEditor` to return your own custom editor, and then
modify your CMake to point to your new implementation of `RNBO_JuceAudioProcessor`
instead of the one that comes with your export.
2. After you've copied the file, modify your CMake to point to your custom 
implementation.
```
target_sources(RNBOAudioPlugin PRIVATE
  "src/BlobJuceAudioProcessor.cpp"
  "src/BlobAudioProcessorEditor.cpp"
  "${RNBO_CPP_DIR}/RNBO.cpp"
  ${RNBO_CLASS_FILE}
  )
```
As you can see, I've renamed the file to BlobJuceAudioProcessor.
3. Now, modify `createEditor` to return an instance of your custom editor.
```
AudioProcessorEditor* JuceAudioProcessor::createEditor()
{
	return new BlobAudioProcessorEditor(this, _rnboObject);
}
```
4. Okay, now we're finally ready to create the editor itself. I'd start by
copying the editor from `export/rnbo/adapters/juce/RNBO_JuceAudioProcessorEditor.cpp`
and renaming it. I'm gonna rename it to `BlobAudioProcessorEditor.cpp`.
5. Now we're ready to bring in our sliders. Put two sliders on the bottom, one for 
`harmonics` and one for `overblow`. 
6. Connect these up, optionally using some debouncing.
7. Now we can chuck in our little blob friend. Copy the `BlobComponent.h` file to 
our local repo, and lets add him to the interface. 
8. Modify all the resizing code so that we can drag stuff around and it all just works.
9. Connect up the message listeners so that we can activate the blob with a message from
our outport.
10. Add more blobs? That's a fun thing to do.