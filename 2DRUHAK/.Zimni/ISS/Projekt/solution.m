% Solution for ISS Project 2017/2018
% Tested and developed on melin
% Run as matlab -r "run('solution.m')"
% @author Jakub "Ash258" Čábera <xcaber00@stud.fit.vutbr.cz>

fileName = 'xcaber00.wav';
[s, FS] = audioread(fileName);
N = length(s);

% Task 1 ✔️ 0.5
disp('TASK1');
	audioinfo(fileName)
	%             Filename: '/homes/eva/xc/xcaber00/Projekty/ISS/xcaber00.wav'
	%    CompressionMethod: 'Uncompressed'
	%          NumChannels: 1
	%           SampleRate: 16000
	%         TotalSamples: 16000
	%             Duration: 1
	%                Title: []
	%              Comment: []
	%               Artist: []
	%        BitsPerSample: 16
disp('END OF TASK1');

% For task 2 and 7
hm = 0.02 * FS;
wf = 0.8 * FS;

% Task 2 ✔️ 0.5
% @see https://www.fit.vutbr.cz/study/courses/ISS/public/proj_studijni_etapa/3_sound/3_sound.pdf
disp('TASK2');
	x = s(wf:(wf+hm-1));
	N = length(x);
	G = 10 * log10(1/N * abs(fft(x)).^2);	% PSD
	G = G(1:N/2);							% Correction of samples count
	f = (0:N/2-1)/N * FS;					% Frequency axis
	plot(f, G); title('Spektrum vstupního signálu xcaber00.wav'); xlabel('f [Hz]'); ylabel('PSD [dB]'); grid;
	print -dpng 'result/task2.png';
	disp('    Printed result/task2.png');
disp('END OF TASK2');

% Task 3 ✔️ 0.5
disp('TASK3');
	disp('    Maximum modulu spektra: ');
	getmaxfreq(s, FS);
disp('END OF TASK3');

% For task 4, 5, 6 and 7
a = [1, 0.2289, 0.4462];
b = [0.2324, -0.4112, 0.2324];

% Task 4 ✔️ 0.5
% @see https://www.fit.vutbr.cz/study/courses/ISS/public/proj_studijni_etapa/3_sound/3_sound.pdf
% Added zero index as document say that, A0 = 1
disp('TASK4');
	zplane(b, a); print -dpng 'result/task4.png';
	p = roots(a);
	if (isempty(p) | abs(p) < 1)
		disp('    Stabilní.');
	else
		disp('    Nestabilní');
	end
	disp('    Printed result/task4.png');
disp('END OF TASK4');

% Task 5 ✔️ 0.5
disp('TASK5');
	H = freqz(b, a, 256);
	f = (0:255)/256 * FS/2;
	plot(f,abs(H)); grid; xlabel('f [Hz]'); ylabel('|H(f)|'); print -dpng 'result/task5.png'
	disp('    Printed result/task5.png');
disp('END OF TASK5');

% Task 6 ✔️ 0.5
disp('TASK6');
	filtered = filter(b, a, s);
	f = (0:N/2-1)/N * FS;
	F = abs(fft(filtered));
	F = F(1:N/2);
	plot(f, F); xlabel('f [Hz]'); grid; print -dpng 'result/task6.png';
	disp('    Printed result/task6.png');
disp('END OF TASK6');

% Task 7 ✔️ 0.5
disp('TASK7');
	disp('    Maximum modulu spektra: ');
	getmaxfreq(filtered, FS);
disp('END OF TASK7');

% %%%%%%%%%%%%%%%%%%%%%%%%%%%
% Task 8 ❌
disp('TASK8');
disp('END OF TASK8');

% For task 9 and 10
Rv = zeros(1,100);

% Task 9 ✔️ 0.5
disp('TASK9');
	x = s; % Duplicate for backup
	N = FS; % Duplicate for backup
	krange = -50:50;
	for k = krange,
		result = 0;
		for n = 1:N,
			if (n + k > 0) && (n + k < N)
				result = result + x(n) * x(n + k);
			end
		end
		Rv(k + 51) = 1 / n * result;
	end
	stem(krange, Rv); xlabel('k'); ylabel('R[k]'); print -dpng 'result/task9.png'
	disp('    Printed result/task9.png');
disp('END OF TASK9');

% Task 10 ✔️ 0.5
disp('TASK10');
	disp('    Hodnota R[10]:');
	disp(Rv(10));
disp('END OF TASK10');

% For task 11, 12, 13
[h, p, r, check] = hist2opt(0, 10, s);

% %%%%%%%%%%%%%%%%%%%%%%%%%%%
% Task 11
disp('TASK11');
	% plot3(h, p, r); print -dpng 'result/task11.png'
disp('END OF TASK11');

% Task 12
disp('TASK12');
	if check == 1
		disp('    It''s correct function.');
	else
		disp('    It''s not correct function.');
	end
disp('END OF TASK12');

% %%%%%%%%%%%%%%%%%%%%%%%%%%%
% Task 13
disp('TASK13');
	disp(r);
disp('END OF TASK13');

exit(0);
