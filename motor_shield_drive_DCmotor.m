clear 

a = arduino('com16','uno','libraries','I2C');
%  digitalWrite(12, LOW); //Establishes backward direction of Channel A
%  digitalWrite(9, LOW);   //Disengage the Brake for Channel A
%  analogWrite(3, 123);   //Spins the motor on Channel A at half speed
t=1;
while t<500
    % spines the motor in direction A
 writeDigitalPin(a,'D12',1); 
 writeDigitalPin(a,'D9',0);
 writePWMVoltage(a,'D3',4.9);
 pause(2)
 writeDigitalPin(a,'D9',1);
 writePWMVoltage(a,'D3',0);
 pause(2)
 
 % spines the motor in direction -A
 writeDigitalPin(a,'D12',1); 
 writeDigitalPin(a,'D9',0);
 writePWMVoltage(a,'D3',3); % out put 3/9 volts, total 12v
 pause(2)
 writeDigitalPin(a,'D9',1);
 writePWMVoltage(a,'D3',0);
 pause(2)
 
 t=t+1;
end 
stop('a')

 