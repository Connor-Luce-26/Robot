function [T0f] = fwdkin_allresults(a, alpha, d, theta, print_intermediates) 
% Calculates forward kinematics given an input of denavit-hartenberg (did I
% spell that right?) parameters 

T0f = eye(4); % Transformation TO frame 0 FROM final frame
for i = length(a):-1:1
    TBackOne = [    cos(theta(i))   -sin(theta(i))*cos(alpha(i))    sin(theta(i))*sin(alpha(i))     a(i)*cos(theta(i))
                    sin(theta(i))   cos(theta(i))*cos(alpha(i))     -cos(theta(i))*sin(alpha(i))    a(i)*sin(theta(i))
                    0               sin(alpha(i))                   cos(alpha(i))                   d(i)
                    0               0                               0                               1];
    
    if(print_intermediates)
        fprintf("Transform from %d to %d:", i, i-1);
        TBackOne
    end
    T0f = TBackOne*T0f;
end
end