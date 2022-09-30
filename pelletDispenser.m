clear 
delete(instrfind({'Port'},{'COM8'}))
a  = arduino('com8','uno','libraries','I2C');
a.pinMode(8,'output');
a.pinMode(9,'output');
a.pinMode(12,'output');
a.pinMode(13,'output');
a.pinMode(3,'output');
a.pinMode(11,'output');
% a.pinMode(5,'input');
if monkeytouched
    driveMotor(a)
end



function driveMotor(a)
 delaylength = 0.01;
 nbstep      = 8;
 for i      = 1:nbstep
  check_sensor(a);
  writeDigitalPin(a,'D9', 0);   %//ENABLE CH A
  writeDigitalPin(a,'D8', 1);   %//DISABLE CH B
  writeDigitalPin(a,'D12',1);   %//Sets direction of CH A
  writePWMVoltage(a,'D3', 5);    %//Moves CH A
  pause(delaylength);
   
  check_sensor(a);
  writeDigitalPin(a,'D9', 1);   %//DISABLE CH A
  writeDigitalPin(a,'D8', 0);   %//ENABLE CH B
  writeDigitalPin(a,'D13',0);  %//Sets direction of CH B
  writePWMVoltage(a,'D11',5);   %//Moves CH B
  pause(delaylength);
  
  check_sensor(a);
  writeDigitalPin(a,'D9', 0); %//ENABLE CH A
  writeDigitalPin(a,'D8', 1); %//DISABLE CH B
  writeDigitalPin(a,'D12',0); %//Sets direction of CH A
  writePWMVoltage(a,'D3', 5);  %//Moves CH A
  pause(delaylength);
  
  check_sensor(a);
  writeDigitalPin(a,'D9', 1);   %//DISABLE CH A
  writeDigitalPin(a,'D8', 0);   %//ENABLE CH B
  writeDigitalPin(a,'D13',1);  %//Sets direction of CH B
  writePWMVoltage(a,'D11',5);        %//Moves CH B
  pause(delaylength);
 end
  stop_motor(a);
end
%   clear(a);
function stop_motor(a)
    delaylength    = 0.01;% in seconds
    writeDigitalPin(a,'D9',1);  %//DISABLE CH A
    writePWMVoltage(a,'D3', 0); %//stop Move CH A
    writeDigitalPin(a,'D8',1);  %//DISABLE CH B
    writePWMVoltage(a,'D11',0); %//stop Move CH B 
    pause(delaylength);
end

function check_sensor(a)
  sensor    = readDigitalPin(a,'D5');
  if sensor ==0
     stop_motor(a);
  end
end