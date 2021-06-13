% Proceso matlab

% Cargamos los archivos WAV

bypass = audioread('<your_own_path>\\wav\bypass.wav');
pres1 = audioread('<your_own_path>\\wav\pres1.wav');
pres2 = audioread('<your_own_path>\\wav\pres2.wav');
pres3 = audioread('<your_own_path>\\wav\pres3.wav');
pres4 = audioread('<your_own_path>\\wav\pres4.wav');
pres5 = audioread('<your_own_path>\\wav\pres5.wav');

% Observamos que la duración mínima es 1513865 samples, valor que asignamos a $minLength

minLength = length(pres3)

% acortamos las matrices al mínimo de samples calculado para dejarlas igual de tamaño, previa edición exacta del comienzo y final del archivo con Adobe Audition

bypass(minLength+1:length(bypass),:)=[]
pres1(minLength+1:length(pres1),:)=[]
pres2(minLength+1:length(pres2),:)=[]
pres4(minLength+1:length(pres4),:)=[]
pres5(minLength+1:length(pres5),:)=[]

% procedemos a calcular el #STOI de cada preset respecto a la recepción en bypass con el script proporcionado por https://ceestaal.nl/code/ 
% Usage: d = taal2011(sigclean, sigproc, fs);

fs=44100; //frecuencia de muestreo de las grabaciones



% procedemos a calcular el índice de articulación 

stoi1=stoi(bypass,pres1,fs); % 0.659148180240089 
stoi2=stoi(bypass,pres2,fs); % 0.660393566847954
stoi3=stoi(bypass,pres3,fs); % 0.661040874047525
stoi4=stoi(bypass,pres4,fs); % 0.662624514737910
stoi5=stoi(bypass,pres5,fs); % 0.664876961868985