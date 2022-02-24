clear 

a = arduino('com13','uno','libraries','I2C');
for i=1:50
 writeDigitalPin(a,'D2',1);
 pause(0.2)
 writeDigitalPin(a,'D2',0);
 pause(1)
 i
end
x=4;
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 



brightness_step = (5-0)/20; 
   for i = 1:20
      writePWMVoltage(a, 'D11', brightness_step*i);
      pause(0.1);
   end
    for i = 1:20
      writePWMVoltage(a, 'D11',5-brightness_step*i);
      pause(0.1);
   end