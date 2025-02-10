% 选择串口 Monitor COM 端口  
arduinoPort = 'COM3'; % 确保更改为你的 Arduino 连接的 COM 端口  
serialObj = serialport(arduinoPort,  9600); % 创建串口对象  

% 发送 'H' 以点亮 LED 
for i=1:10
    write(serialObj, 'H','char');
    pause(0.5); % 等待 1 秒

    % 发送 'L' 以关闭 LED
    write(serialObj, 'L','char');
    pause(0.5); % 等待 1 秒

    % 读取 Arduino 的响应
    while serialObj.NumBytesAvailable > 0
        response = readline(serialObj);
        disp(['Arduino: ', response]) % 显示 Arduino 返回的值
    end
end
% 关闭串口  
clear serialObj