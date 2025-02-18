function angle = arm(x, y, z, xAngle, yAngle, zAngle)
a = [0, 4.743, 4.743, 0, 0, 2.903];
d = [3.685, 0, 0, -4.632, 4.362, 4.349];
alpha = deg2rad([0, 90, 0, -90, 90, 0]);
theta = deg2rad([0, 90, 0, -90, 0, 0]);
dhparams = [a; alpha; d; theta]';
robot = rigidBodyTree;
bodies = cell(6,1);
joints = cell(6,1);
for i = 1:6
    bodies{i} = rigidBody(['body' num2str(i)]);
    joints{i} = rigidBodyJoint(['jnt' num2str(i)],"revolute");
    setFixedTransform(joints{i},dhparams(i,:),"dh");
    bodies{i}.Joint = joints{i};
    if i == 1
        addBody(robot,bodies{i},"base")
    else
        addBody(robot,bodies{i},bodies{i-1}.Name)
    end
end
ik = inverseKinematics("RigidBodyTree",robot);
weights = [0 0 0 1 1 1];
initialguess = homeConfiguration(robot);
TF = tform(se3(deg2rad([xAngle, yAngle, zAngle]),"eul","XYZ", [x, y, z]));
angle = [0, 0, 0, 0, 0, 0];
[configSoln,~] = ik("body6",TF,weights,initialguess);
for i=1:6
    angle(i) = configSoln(1).JointPosition;
end
angle = rad2deg(angle);