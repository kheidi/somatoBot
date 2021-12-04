%% Somato-Bot Torque Estimates
close all; clear;
%% Physical Properties
I_L1_o = 2.038E+05*(10^-9); %Izz at origen (kg mˆ2)
m1 = 30.263/1000; %kg

I_L2_o = 1.362E+05*(10^-9); %Izz at origen (kg mˆ2)
m2 = 29.988/1000; %g

l_L2 = 190.755/1000; %m

%% Acceleration
t = 0.2:0.01:3; %s
theta_travelled = degtorad(180); %rad
alpha = (2*theta_travelled)./(t.^2); %rad/s2

% Average speed in RPM
RPM = ((.5*60)./(t));

%% Inertia
I_sum = I_L1_o + I_L2_o + m2*(l_L2^2); %kg m^2


%% Minimum torque and power estimates
torque = (I_sum.*alpha); %Nm
power = torque.*(theta_travelled./t); %W

torque = torque * 10.197162129779; %convert to kg cm
figure
subplot(2,2,1)
plot(RPM,torque)
xlabel('RPM')
ylabel('Torque (kg cm)')
yline(0.54)
yline(0.86)
xline(0.25)

subplot(2,2,2)
plot(t,torque)
xlabel('Time to travel 180 deg (s)')
ylabel('Torque (kg cm)')
yline(0.54)
yline(0.86)
xline(0.25)

subplot(2,2,3)
plot(RPM, power)
xlabel('RPM')
ylabel('Power')

subplot(2,2,4)
plot(t, power)
xlabel('Time to travel 180 deg')
ylabel('Power')