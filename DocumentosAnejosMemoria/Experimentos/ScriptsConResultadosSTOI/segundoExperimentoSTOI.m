% Proceso matlab

% hombreAdulto
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% Cargamos los archivos WAV

bypass = audioread('<your_own_path>\\hombreAdulto\haBypass.wav');
pres1 = audioread('<your_own_path>\\hombreAdulto\haPres1.wav');
pres2 = audioread('<your_own_path>\\hombreAdulto\haPres2.wav');
pres3 = audioread('<your_own_path>\\hombreAdulto\haPres3.wav');
pres4 = audioread('<your_own_path>\\hombreAdulto\haPres4.wav');
pres5 = audioread('<your_own_path>\\hombreAdulto\haPres5.wav');

% Observamos que la duración mínima es 1560090 samples, valor que asignamos a $minLength

minLength = length(bypass)

% acortamos las matrices al mínimo de filas calculado para dejarlas igual de tamaño


pres1(minLength+1:length(pres1),:)=[];
pres2(minLength+1:length(pres2),:)=[];
pres3(minLength+1:length(pres3),:)=[];
pres4(minLength+1:length(pres4),:)=[];
pres5(minLength+1:length(pres5),:)=[];

% procedemos a calcular el #STOI de cada preset respecto a la recepción en bypass 
% Usage: d = taal2011(sigclean, sigproc, fs);

fs=44100; //frecuencia de muestreo de las grabaciones



% procedemos a calcular el STOI 

stoi1=stoi(bypass,pres1,fs); % 0.964994163999879
stoi2=stoi(bypass,pres2,fs); % 0.963651376250167
stoi3=stoi(bypass,pres3,fs); % 0.970414771971897
stoi4=stoi(bypass,pres4,fs); % 0.964494466424379
stoi5=stoi(bypass,pres5,fs); % 0.963203910889487

% mujerAdulta
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

bypass = audioread('<your_own_path>\\mujerAdulta\maBypass.wav');
pres1 = audioread('<your_own_path>\\mujerAdulta\maPres1.wav');
pres2 = audioread('<your_own_path>\\mujerAdulta\maPres2.wav');
pres3 = audioread('<your_own_path>\\mujerAdulta\maPres3.wav');
pres4 = audioread('<your_own_path>\\mujerAdulta\maPres4.wav');
pres5 = audioread('<your_own_path>\\mujerAdulta\maPres5.wav');


% Observamos que la duración mínima es 1668512 samples, valor que asignamos a $minLength

minLength = length(bypass);

% acortamos las matrices al mínimo de filas calculado para dejarlas igual de tamaño


pres1(minLength+1:length(pres1),:)=[];
pres2(minLength+1:length(pres2),:)=[];
pres3(minLength+1:length(pres3),:)=[];
pres4(minLength+1:length(pres4),:)=[];
pres5(minLength+1:length(pres5),:)=[];

% procedemos a calcular el STOI 

stoi1=stoi(bypass,pres1,fs); % 0.993788066382967
stoi2=stoi(bypass,pres2,fs); % 0.633845024294314
stoi3=stoi(bypass,pres3,fs); % 0.978575715090363
stoi4=stoi(bypass,pres4,fs); % 0.992793094504785
stoi5=stoi(bypass,pres5,fs); % 0.990173534550311


% hombreJoven
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

% Cargamos los archivos WAV

bypass = audioread('<your_own_path>\\hombreJoven\hjBypass.wav');
pres1 = audioread('<your_own_path>\\hombreJoven\hjPres1.wav');
pres2 = audioread('<your_own_path>\\hombreJoven\hjPres2.wav');
pres3 = audioread('<your_own_path>\\hombreJoven\hjPres3.wav');
pres4 = audioread('<your_own_path>\\hombreJoven\hjPres4.wav');
pres5 = audioread('<your_own_path>\\hombreJoven\hjPres5.wav');

% Observamos que la duración mínima es 1390742 samples, valor que asignamos a $minLength

minLength = length(pres5);

% acortamos las matrices al mínimo de filas calculado para dejarlas igual de tamaño


pres1(minLength+1:length(pres1),:)=[];
pres2(minLength+1:length(pres2),:)=[];
pres3(minLength+1:length(pres3),:)=[];
pres4(minLength+1:length(pres4),:)=[];
bypass(minLength+1:length(bypass),:)=[];

% procedemos a calcular el #STOI de cada preset respecto a la recepción en bypass 
% Usage: d = taal2011(sigclean, sigproc, fs);

fs=44100; //frecuencia de muestreo de las grabaciones



% procedemos a calcular el STOI 

stoi1=stoi(bypass,pres1,fs); % 0.988994967724525
stoi2=stoi(bypass,pres2,fs); % 0.985023163332677
stoi3=stoi(bypass,pres3,fs); % 0.973358456780189
stoi4=stoi(bypass,pres4,fs); % 0.989840490376182
stoi5=stoi(bypass,pres5,fs); % 0.988650320823085



% mujerJoven
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

% Cargamos los archivos WAV

bypass = audioread('<your_own_path>\\mujerJoven\mjBypass.wav');
pres1 = audioread('<your_own_path>\\mujerJoven\mjPres1.wav');
pres2 = audioread('<your_own_path>\\mujerJoven\mjPres2.wav');
pres3 = audioread('<your_own_path>\\mujerJoven\mjPres3.wav');
pres4 = audioread('<your_own_path>\\mujerJoven\mjPres4.wav');
pres5 = audioread('<your_own_path>\\mujerJoven\mjPres5.wav');

% Observamos que la duración mínima es 1366804 samples, valor que asignamos a $minLength

minLength = length(bypass);

% acortamos las matrices al mínimo de filas calculado para dejarlas igual de tamaño


pres1(minLength+1:length(pres1),:)=[];
pres2(minLength+1:length(pres2),:)=[];
pres3(minLength+1:length(pres3),:)=[];
pres4(minLength+1:length(pres4),:)=[];
pres5(minLength+1:length(pres5),:)=[];

% procedemos a calcular el #STOI de cada preset respecto a la recepción en bypass 
% Usage: d = taal2011(sigclean, sigproc, fs);

fs=44100; //frecuencia de muestreo de las grabaciones



% procedemos a calcular el STOI 

stoi1=stoi(bypass,pres1,fs); % 0.090612022743171
stoi2=stoi(bypass,pres2,fs); % 0.087482096663564
stoi3=stoi(bypass,pres3,fs); % 0.092278400401957
stoi4=stoi(bypass,pres4,fs); % 0.085566038068146
stoi5=stoi(bypass,pres5,fs); % 0.086889520802865

