
clear; close all
 a = 0;  b=1; tfinal = 0.5
 m = 20; 
 m = 40;
% m = 80;

 h = (b-a)/m; k = 0.8*h; mu = k/h; mu1=mu*mu/2.0;

 t = 0; n = fix(tfinal/k);
 y1 = zeros(m+1,1); y2=y1; y3=y2; x=y1;

 for i=1:m+1,
   x(i) = a + (i-1)*h;          % The grid.
   y1(i) = u0(x(i));            % Initial value
   y2(i) = 0;
 end

figure(1); plot(x,y1); hold; axis([0 1 -0.5 1.5]);
pause(1)

t = 0;    % Use Lax-Wendroff to get U^1.
y1(1)=bc(t); y2(1)=bc(t+k);
for i=2:m
  y2(i)= y1(i)-mu*(y1(i+1)-y1(i-1))/2 + mu1*(y1(i+1)-2*y1(i)+y1(i-1));
end
i = m+1;
y2(i)=y1(i)-mu*(3*y1(i)-4*y1(i-1)+y1(i-2))/2+mu1*(y1(i)-2*y1(i-1)+y1(i-2));
plot(x,y2); pause(0.5)

 t = k; 
 for j=2:n,                    % Starting time loop.
   y1(1)=bc(t); y2(1)=bc(t+k);
   for i=2:m
     y3(i)= y1(i)-mu*(y2(i+1)-y2(i-1));
   end
   i = m+1;
   y3(i)=y2(i)-mu*(3*y2(i)-4*y2(i-1)+y2(i-2))/2+mu1*(y2(i)-2*y2(i-1)+y2(i-2));

%   plot(x,y3); pause(0.5)

   t = t + k; y1 = y2; y2=y3;
 end

 u_e = zeros(m+1,1);
 for i=1:m+1
   u_e(i) = uexact(t,x(i));
 end

 max(abs(u_e-y3))

 plot(x,y3,':',x,u_e)
   
figure(2); plot(x,u_e-y3)

