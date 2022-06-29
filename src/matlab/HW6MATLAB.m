clc;
clear;

%Initialize Parameters
Rsig = 100000;
R1 = 3000000;
R2 = 1000000;
RD = 4700;
RS = 560000;
RL = 10000;
gm = 0.00177;
CG = 0.2e-6;
CS = 28e-6;
CD = 100e-6;
%Find parallel combinations
R1parR2 = (R1*R2)/(R1+R2);
RSpargm = (RS/gm)/(RS +1/gm);
%Calculate gains
Ag = R1parR2/(Rsig+R1parR2);
As = gm;
Ad = RD/(RD+RL);
%Calculate K
K = RL*Ag*As*Ad;
% Find angular frequencies
wcg = 1/((CG)*(Rsig+R1parR2));
wcd = 1/((CD)*(RD+RL));
wcsz = 1/(RS*CS);
wcsp = 1/(CS*RSpargm);
chng = 1/(2*pi)
% Declare domain and range
% Magnitiude of the transfer function has the form 
% x^(2)(x+a)/(x+b)(x+c)(x+d)
% Find the magnitude by converting to a+bj form
domain = 0.001:0.0001:1000;
range = K.*((((domain./chng).^(6))+((domain./chng).^(2).*wcsz).^(2))./(((domain./chng).*(wcg.*wcsp + wcg.*wcd + wcsp.*wcd)-((domain./chng)).^(3)).^(2)+ (wcd.*wcg.*wcsp-((domain./chng).^(2).*((wcg)+(wcsp)+(wcd)))).^(2))).^(1/2);
semilogx(domain,20*log10(range), 'b', 'LineWidth', 2);

xlabel('Frequency, f (Hz)')
ylabel('Response Magnitude, |H(s)| (dB)')
grid on
hold on
numFileName = 'HW6Excel.xlsx';
numericalData = xlsread(numFileName);
semilogx(numericalData(:,1),20*log10(numericalData(:,2)),'--r', 'LineWidth', 2);
xlim([0.001 1000])
ylim([-160 60])
title("MOSFET Circuit Analysis Bode Plot");

x1 = wcsz/(2*pi);
x2 = wcd/(2*pi);
x3 = wcg/(2*pi);
x4 = wcsp/(2*pi);
x = [x1 x2 x3 x4];
y1 = K.*((((x1/chng).^(6))+((x1/chng).^(2).*wcsz).^(2))./(((x1/chng).*(wcg.*wcsp + wcg.*wcd + wcsp.*wcd)-((x1/chng)).^(3)).^(2)+ (wcd.*wcg.*wcsp-((x1/chng).^(2).*((wcg)+(wcsp)+(wcd)))).^(2))).^(1/2);
y1F = 20*log10(y1)
y2 = K.*((((x2/chng).^(6))+((x2/chng).^(2).*wcsz).^(2))./(((x2/chng).*(wcg.*wcsp + wcg.*wcd + wcsp.*wcd)-((x2/chng)).^(3)).^(2)+ (wcd.*wcg.*wcsp-((x2/chng).^(2).*((wcg)+(wcsp)+(wcd)))).^(2))).^(1/2);
y2F = 20*log10(y2)
y3 = K.*((((x3/chng).^(6))+((x3/chng).^(2).*wcsz).^(2))./(((x3/chng).*(wcg.*wcsp + wcg.*wcd + wcsp.*wcd)-((x3/chng)).^(3)).^(2)+ (wcd.*wcg.*wcsp-((x3/chng).^(2).*((wcg)+(wcsp)+(wcd)))).^(2))).^(1/2);
y3F = 20*log10(y3)
y4 = K.*((((x4/chng).^(6))+((x4/chng).^(2).*wcsz).^(2))./(((x4/chng).*(wcg.*wcsp + wcg.*wcd + wcsp.*wcd)-((x4/chng)).^(3)).^(2)+ (wcd.*wcg.*wcsp-((x4/chng).^(2).*((wcg)+(wcsp)+(wcd)))).^(2))).^(1/2);
y4F = 20*log10(y4)
y = [y1F y2F y3F y4F];
plot(x,y,'o');
labels = {"Zero (0.0102, -103) ", "Pole 1 (0.108, -47) ", "Pole 2 (0.936 ,-9.8) ", "Pole 3 (10.07, 10.91) "};
text(x,y,labels,'VerticalAlignment','top','HorizontalAlignment','left');
legend('Analytical','Numerical', "Critical Points");

