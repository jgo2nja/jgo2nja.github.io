
clear
clc

tau = 57;
aT = 1/tau;

domain = 0:0.1:200;

r5 = ((-2*log(0.5))/aT^(2))^(1/2);
r7 = ((-2*log(0.3))/aT^(2))^(1/2);
r9 = ((-2*log(0.1))/aT^(2))^(1/2);

pdf = aT^(2).*domain.*exp(-0.5*aT^(2).*domain.^(2));

cdf = 1-exp(-0.5*aT^(2).*domain.^(2));
subplot(1,3,1)
plot(domain, pdf);
title("PDF of random variable X")
xlabel("Total Distance from T, X (in)")
ylabel("PDF Value, f_{X}(x)")
subplot(1,3,2)
plot(domain, cdf);
title("CDF of random variable X")
xlabel("Total Distance from T, X (in)")
ylabel("CDF Value, F_{X}(x)")
subplot(1,3,3)
domain5 = -r5:0.1:r5
domain7 = -r7:0.1:r7
domain9 = -r9:0.1:r9
range5pos = (r5^(2)-domain5.^(2)).^(1/2);
range5neg = -(r5^(2)-domain5.^(2)).^(1/2);
range7pos = (r7^(2)-domain7.^(2)).^(1/2);
range7neg = -(r7^(2)-domain7.^(2)).^(1/2);
range9pos = (r9^(2)-domain9.^(2)).^(1/2);
range9neg = -(r9^(2)-domain9.^(2)).^(1/2);
plot(domain5, range5pos, 'b');
hold on
plot(domain7, range7pos, 'k');
hold on
plot(domain9, range9pos, 'r');
hold on
plot(domain5, range5neg, 'b');
hold on
plot(domain7, range7neg, 'k');
hold on
plot(domain9, range9neg, 'r');
hold on
plot(0,0, '.');
text(0,0,"T");
title("Drop Area for CDF values of 0.5, 0.7, and 0.9");
xlabel("X distance from T, Y_{1} (in)");
ylabel("Y distance from T, Y_{2} (in)");
legend("p = 0.5", "p = 0.7", "p = 0.9")
hold off

rand_num_array = zeros(150000,1);
rand_num_array(1) = 1000;
a = 24693;
c = 3967;
K = 2^(18);
for i=2:1:150000
    x_previous = rand_num_array(i-1);
    x_next = mod(a*x_previous + c, K)
    rand_num_array(i) = x_next;
end

rand_num_array_F = rand_num_array/K

estimateCount = 110;

n1 = 10;
n2 = 30;
n3 = 50;
n4 = 100;
n5 = 250;
n6 = 500;
n7 = 1000;
mn_array = zeros(770,1);
for i=2:1:111
    mn_local = zeros(n1,1)
    for j=(i-1)*n1:1:i*n1
        x_realization = (-2*log(1-rand_num_array_F(j+1))/aT^(2))^(1/2)
        mn_local((j-(i-1)*n1)+1) = x_realization
    end
    mean1 = mean(mn_local);
    mn_array(i-1) = mean1;
end
for i=2:1:111
    mn_local = zeros(n2,1)
    for j=(i-1)*n2:1:i*n2
        x_realization = (-2*log(1-rand_num_array_F(j+1))/aT^(2))^(1/2)
        mn_local((j-(i-1)*n2)+1) = x_realization
    end
    mean1 = mean(mn_local);
    mn_array(109+i) = mean1;
end
for i=2:1:111
    mn_local = zeros(n3,1)
    for j=(i-1)*n3:1:i*n3
        x_realization = (-2*log(1-rand_num_array_F(j+1))/aT^(2))^(1/2)
        mn_local((j-(i-1)*n3)+1) = x_realization
    end
    mean1 = mean(mn_local);
    mn_array(219+i) = mean1;
end
for i=2:1:111
    mn_local = zeros(n4,1)
    for j=(i-1)*n4:1:i*n4
        x_realization = (-2*log(1-rand_num_array_F(j+1))/aT^(2))^(1/2)
        mn_local((j-(i-1)*n4)+1) = x_realization
    end
    mean1 = mean(mn_local);
    mn_array(329+i) = mean1;
end
for i=2:1:111
    mn_local = zeros(n5,1)
    for j=(i-1)*n5:1:i*n5
        x_realization = (-2*log(1-rand_num_array_F(j+1))/aT^(2))^(1/2)
        mn_local((j-(i-1)*n5)+1) = x_realization
    end
    mean1 = mean(mn_local);
    mn_array(439+i) = mean1;
end
for i=2:1:111
    mn_local = zeros(n6,1)
    for j=(i-1)*n6:1:i*n6
        x_realization = (-2*log(1-rand_num_array_F(j+1))/aT^(2))^(1/2)
        mn_local((j-(i-1)*n6)+1) = x_realization
    end
    mean1 = mean(mn_local);
    mn_array(549+i) = mean1;
end
for i=2:1:111
    mn_local = zeros(n7,1)
    for j=(i-1)*n7:1:i*n7
        x_realization = (-2*log(1-rand_num_array_F(j+1))/aT^(2))^(1/2)
        mn_local((j-(i-1)*n7)+1) = x_realization
    end
    mean1 = mean(mn_local);
    mn_array(659+i) = mean1;
end

ndomain = 1:1:770;
mean = sqrt(pi/2)*57;
plot(ndomain,mn_array,'x');
yline(mean, 'r', "lineWidth", 1);
legend("Sample Mean Instance", "Actual Mean")
xline(110);
xline(220);
xline(330);
xline(440);
xline(550);
xline(660);
xlabel("Sample Size, n")
ylabel("Sample Mean Value, M_{n}")
title("Sample Mean of the Random Variable X for Various Sample Sizes")
xlim([0 770])