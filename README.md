
# Improving Streaming


# https://github.com/ealcober/Improving-Streaming.git

Code based on (1) Rudrich SimpleCompressor and (2) Alermi pd-HighPass for academic research looking for relations between compression and equalization and voice intelligibillity.
All code in (1) and (2) and the one developed & provided in this repository is under GNU General Public License v3.0 whose manifest can be found on root folder.

### References
1. https://github.com/DanielRudrich/SimpleCompressor
2. https://github.com/alermi/JUCE-HighPass

### Purpose
The purpose of this project is to develop a digital audio processor, based on traditional signal enhancement tools. We will broadcast voice through it, and variations detected on voice intelligibility will be studied, looking for relations within different configuration parameters applied, creating an objective process to measure its impact.

## What do I need to Run Improving Streaming Plugin?
1. Download and install OBS from: https://obsproject.com/es/download
2. Download ProJucer and locate it under your c:\ root folder. Download from: https://juce.com/get-juce/download
3. Follow "step by step compile and obs usage guide.pptx" file to set up Improving Streaming plugin on OBS and begin squeezing your voice!

### contains binary files compiled for x64 with VST2 SDK
1. \CodigoPlugin\bin\ 

### this is the file you must open with JUCE: Projucer Project File 
2. \CodigoPlugin\Improving Streaming\examples\ImprovingStreaming\ImprovingStreaming.jucer
### and the place where you can find both main project code files: Editor & Processor
   \CodigoPlugin\Improving Streaming\examples\ImprovingStreaming\Source

### contains some initial design ideas as mockups: brainstorm at first stages of developing
3. \DocumentosAnejosMemoria\Desarrollo\Mockups\

### you can find how finally Improving Streaming looks :)
4. \DocumentosAnejosMemoria\Desarrollo\Screenshots

### organized by folders & sub-folders camelCase named in Spanish, you can find there
5. \DocumentosAnejosMemoria\Experimentos

	5.1. \DocumentosAnejosMemoria\Experimentos\BrutosyAudiosSpeechToTextConResultados
	### videos of live recording via twitch of voice streamed during this TFG experiments, first, and second of them
	### google and microsoft speech to text services transcriptions per audio file
	### dwdiff linux command output to compare bypass recognized text with the text recognized wich each preset
	### powerBI source files
	### powerBI-PDF formatted analysis results
	### Excel files with tabular results

	5.2. \DocumentosAnejosMemoria\Experimentos\ScriptsConResultadosSTOI
	### Matlab Scripts used on each experiment for STOI calculation and results pasted as comment

	5.3.DocumentosAnejosMemoria\Experimentos\VideosCuencoGoogleTeams
	### Some recordings tryng to test auto configurable IA noise cancellation sollutions from Google & Microsoft with a Tibetan bowl

### This repository includes:
- Code for *IMPROVING AUDIO QUALITY IN STREAMING APPLICATIONS* TFG.
- Additional Scripts used during development
- Original videos and audios of both experiments
- Step by Step guide to finally build your own DLL VST2 or EXE as Standalone App from this repo
- SDK for VST 2.0 development vstsdk3610_11_06_2018_build_37.zip file
	- Its an special version, not actually availabe as public dowload cause its recent update to VST3.0 SDK and has been removed.


### Screenshot of the ImprovingStreaming plug-in
![alt text](DocumentosAnejosMemoria/Desarrollo/Screenshots/ImprovingStreaming.PNG)

### Instructions for Compiling and usage with OBS:
1. Can be foud @ "step by step compile and obs usage guide.pptx" file
2. If you prefer use binaries to avoid risky places, just skip compiling part and go straight to OBS audio insertion step by step guide!


