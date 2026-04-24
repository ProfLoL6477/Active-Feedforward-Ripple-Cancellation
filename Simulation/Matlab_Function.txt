function y = fcn(u)
%% Discrete high-pass filter for DC + ripple separation
%% - Robust DC blocker (industry standard)
%% - Stable for large DC offsets
%% - Suitable for STM32 implementation

persistent u_prev y_prev initialized

if isempty(initialized)
    u_prev = u;
    y_prev = 0;
    initialized = true;
end

%% Parameters
fs = 200000;     % sample rate
fc = 900;        % cutoff (Hz)

alpha = exp(-2*pi*fc/fs);

%% DC blocking high-pass filter
y = (u - u_prev) + alpha * y_prev;

%% State update
u_prev = u;
y_prev = y;

%% Intentional inversion
y = -y;

%% Fail-safe
if ~isfinite(y)
    y = 0;
    u_prev = u;
    y_prev = 0;
end
