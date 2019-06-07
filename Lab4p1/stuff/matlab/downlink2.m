%% main function

close all;
clearvars;
delete(instrfindall);

% set up uart
s = serial('COM5', 'BaudRate',115200);
set(s,'InputBufferSize',1024);
fopen(s);

%% main function 2

% set up map
keySet = ...
   {'z', 'x', 'c', 'v', 'b', 'n', 'm', ...
    's', 'd', 'g', 'h', 'j', ...
    'q', 'w', 'e', 'r', 't', 'y', 'u', ...
    '2', '3', '5', '6', '7', ...
    'comma', 'period', 'semicolon', 'quote',...
    'end', 'downarrow', 'pagedown', 'leftarrow', 'clear', 'rightarrow' ...
    'f1', 'f2', 'f3', 'f4'};

ValueSet = ...
   {60, 62, 64, 65, 67, 69, 71, ...
    61, 63, 66, 68, 70, ...
    72, 74, 76, 77, 79, 81, 83, ...
    73, 75, 78, 80, 82, ...
    128, 129, 130, 131, ...
    144, 145, 146, 147, 148, 149, ...
    160, 161, 162, 163};

M = containers.Map(keySet, ValueSet);

% set up key detection
h.fig = figure ;
img = imread('keyboard.png');
image(img);

% set up the timer
h.t = timer ;
h.t.Period = 2 ;
h.t.ExecutionMode = 'fixedRate' ;
h.t.TimerFcn = @timer_calback ;

% set up the Key functions
set( h.fig , 'keyPressFcn'   , {@keyPressFcn_calback, M, keySet, s} ) ;
set( h.fig , 'keyReleaseFcn' , {@keyReleaseFcn_calback, keySet, s} ) ;

guidata( h.fig ,h)
%fclose(s);
%delete(s);


%% helper functions 

function timer_calback(~,~)
    %disp( rand(1) )
end

function keyPressFcn_calback(hobj,evt, M, keySet, s)
    %disp(evt.Key)
    if ismember(evt.Key, keySet)
        h = guidata(hobj);
        if strcmp(h.t.Running,'off')
            start(h.t)
            disp(M(evt.Key))
            for i = (1: 5)
                fwrite(s, M(evt.Key), 'uint8'); 
            end
            for i = (1 : 5)
                fwrite(s, 0, 'uint8');   
            end
        end
    end
end

function keyReleaseFcn_calback(hobj,evt, keySet, s) 
    if ismember(evt.Key, keySet)
        h = guidata(hobj) ;
        stop(h.t)
        disp(255)
        for i = (1: 5)
            fwrite(s, 255, 'uint8'); 
        end
        for i = (1: 5)
            fwrite(s, 0, 'uint8');   
        end
    end
end