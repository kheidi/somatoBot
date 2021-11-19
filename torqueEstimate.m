%% Somato-Bot Torqye Estimates
%% Physical Properties
I_L1_o = 3354.028*(10^-9); %Iyy at origen (kg mˆ2)
m1 = 22.877/1000; %gr

I_L2_o = 60242.454*(10^-9); %Iyy at origen (kg mˆ2)
m2 = 15.799/1000; %g

l_L2 = 130/1000; %m

%% Acceleration
t = 0.5:0.01:3; %s
theta_travelled = degtorad(180); %rad
alpha = (2*theta_travelled)./(t.^2); %rad/s2

% Average speed in RPM
RPM = ((.5*60)./(t));

%% Inertia
I_sum = I_L1_o + I_L2_o + m2*(l_L2^2); %kg m^2


%% Minimum torque and power estimates
torque = (I_sum.*alpha); %Nm
power = torque.*(theta_travelled./t); %W

figure
plot(RPM,torque)
xlabel('RPM')
ylabel('Torque (Nm)')

figure
plot(t,torque)
xlabel('Time to travel 180 deg (s)')
ylabel('Torque (Nm')

figure
plot(RPM, power)
xlabel('RPM')
ylabel('Power')

figure
plot(t, power)
xlabel('Time to travel 180 deg')
ylabel('Power')