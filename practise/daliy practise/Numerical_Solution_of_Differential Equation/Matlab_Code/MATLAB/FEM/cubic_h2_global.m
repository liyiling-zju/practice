% Plot two global cubic function in H^2
clear all; close all;

x=-4:0.1:4; m=length(x); x=x'; y5=zeros(m,1); y6=y5;
x2=-4:2:4;x2=x2'; n= length(x2); yt2=zeros(n,1);

for i=1:m
    if abs(x(i)) >2 
        y5(i) = 0; y6(i) = 0;
    else if x(i) <=0
            [y1,y2,y3,y4] = fem_cubic_h2(x(i)+1); 
            y5(i) = y2; y6(i) = y4;
        else 
            [y1,y2,y3,y4] = fem_cubic_h2(x(i)-1); 
            y5(i) = y1; y6(i) = y3;
        end
    end
end

subplot(211); plot(x,y5)
axis([-4 4 -0.2 1.2])
hold
plot(x2,yt2,'o')
plot(x2,yt2,'x')
plot(x2,yt2,':')

subplot(212); plot(x,y6)
yt = zeros(m,1); hold
plot(x,yt,':')
plot(x2,yt2,'o')
plot(x2,yt2,'x')
