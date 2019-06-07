close all;
clearvars;
delete(instrfindall);

s = serial('COM6', 'BaudRate',115200);
set(s,'InputBufferSize',1024);
fopen(s);

keySet = ...
   {'z', 'x', 'c', 'v', 'b', 'n', 'm', ...
    's', 'd', 'g', 'h', 'j', ...
    'q', 'w', 'e', 'r', 't', 'y', 'u', ...
    '2', '3', '5', '6', '7', ...
    ',', '.', ';', ''''};

ValueSet = ...
   {60, 62, 64, 65, 67, 69, 71, ...
    61, 63, 66, 68, 70, ...
    72, 74, 76, 77, 79, 81, 83, ...
    73, 75, 78, 80, 82, ...
    128, 129, 130, 131};

M = containers.Map(keySet, ValueSet);

while(true)
    try 
        w = waitforbuttonpress;
    catch 
        break;
    end
    if w
        p = get(gcf, 'CurrentCharacter');
        disp(p)
        if ismember(p, keySet)
            %M(user_input)
            for i = (1: 5)
                fwrite(s, M(p), 'uint8'); 
            end
            for i = (1 : 5)
                fwrite(s, 0, 'uint8');   
            end
        end
    end
end

fclose(s);
delete(s);