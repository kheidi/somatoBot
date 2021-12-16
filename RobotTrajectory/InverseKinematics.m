%% General data:
  l1 = 0.153; % [m]
  l2 = 0.140; %[m]
  x0 = 0.03;
  y0 = 0.02;
  PI = 3.141592653589793238;
  r =  0.03;
  w = 200;
  t = 1;

  % Circular Trajectory
  x = ((r*cos(2*PI*w*t))+x0);
  y = ((r*sin(2*PI*w*t))+y0);

%% Inverse Kinematics - My formualas
theta2_rad = acos ((x^2 + y^2 -l1^2 - l2^2) / (2*l1*l2))
theta1_rad = atan(y/x) - atan ((l2*sin (theta2_rad))/(l1 + l2*cos(theta2_rad)))

theta1_angle = theta1_rad* (180/(2*PI))
theta2_angle = theta2_rad* (180/(2*PI))

