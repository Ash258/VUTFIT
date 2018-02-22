function [h,p,r,check] = hist2(y1,y2,x);
% y1 and y2 are column vectors with data (must have same dimension)
% x  are centers of histogram bins for the 2 coordinates.
%    should be equally spaced !!!
% h is the 2-D histogram (y1 distrib in cols, y2 in rows)
%
% p is the estimate of 2-D prob. dens. function
%
% r is he autocorrelation coefficient computed using the theoretical
% formula (5-8 in Sebesta)
%
% ... histogram computation is not very optimized ...

L = length(x);
N = length(y1);

% alloc for hist
h = zeros(L,L); out = 0; % counter of bad samples...

% make a BIG matrix with all values of x ... will actually do something
% like vector quantization.
% first make col vector out of x, then repeat it N times.
xcol = x(:); bigx = repmat(xcol,1,N);

% make rows out of y1 , y2 and do the 'quantization'
yr = y1(:)'; bigy = repmat(yr,L,1);
[dummy,ind1] = min(abs(bigy - bigx));
yr = y2(:)'; bigy = repmat(yr,L,1);
[dummy,ind2] = min(abs(bigy - bigx));

% now just go through the indices and increment respective cases in h
for ii=1:N,
	d1 = ind1(ii);
	d2 = ind2(ii);
	h(d1,d2) = h(d1,d2) + 1;
end

%%% prob dens: will have to normalize
surf = (x(2) - x(1))^2; % surface of one tile
p = h / N / surf;

%%%% autocor coeff
% make col vector out of x and clone it L times.
x = x(:); X1 = repmat(x,1,L);
% make row vector out of x and clone it L times.
x = x'; X2 = repmat(x,L,1);
% now put it together, don't forget to multipl by tile surface
r = sum(sum (X1 .* X2 .* p)) * surf;

%%% check ...
check = sum(sum (p)) * surf;
% disp(['hist2: check -- 2d integral should be 1 and is ' num2str(check)]); % Task 12
