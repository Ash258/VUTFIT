function [maxFreq] = getmaxfreq(signal, FS);
% @see https://www.mathworks.com/matlabcentral/answers/51290-extracting-the-fundamental-frequency-of-a-wav-file
ydft = fft(signal);
freq = 0:FS/length(signal):FS/2;
ydft = ydft(1:length(signal)/2+1);
[maxval,idx] = max(abs(ydft));
maxFreq = freq(idx)
