% Create FreeMASTER ActiveX object.
fmstr = actxserver ('MCB.PCM');
% Write 0x10 value into "var16inc" variable defined in FreeMASTER project.
bSucc = fmstr.WriteVariable('var16inc', 16);
% Read the "var16" variable as defined in FreeMASTER project.
% "!" - immediate performs the command.
var16 = 0;
bSucc = fmstr.ReadVariable('var16');
if bSucc
var16 = fmstr.LastVariable_vValue;
end
% Show the value.
var16
% Configure Matlab to accept safe array as single dimension.
feature('COM_SafeArraySingleDim', 1);
% Write 4 bytes to memory 0x20. WriteMemory function expects SafeArray as input data.
bSucc = fmstr.WriteMemory(32, 4, {11;22;33;44});
% Reads 4 bytes from memory at address of "var32inc" variable.
bSucc = fmstr.ReadMemory('var32inc', 4);
if bSucc
% Reads data of last call the ReadMemory()function.
readMemResult = fmstr.LastMemory_data
end
% Write to memory at pointer. The value of "var8" represents the pointer, 0x02 is offset.
% This is only demonstration !!Beware that wrong value of var8 may cause memory corruption!!
array = [11;22;33;44];
bSucc = fmstr.WriteUIntArray('valueof(var8) + 0x02', 4, 1, {array});