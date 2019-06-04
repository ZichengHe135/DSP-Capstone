close all;
clearvars;

s = serial('COM7', 'BaudRate',115200);
set(s,'InputBufferSize',1024);
fopen(s);

while(true)
    
    user_input = input('write input: ', 's');
    if strcmp(user_input, 'quit')
        break
    end
    %user_input
    fwrite(s, user_input);

end

fclose(s);
delete(s);