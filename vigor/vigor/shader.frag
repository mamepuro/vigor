#version 460

layout(location = 0) out vec4 fragment;
uniform int code;

void main() {
	fragment = vec4(1.0, 0.0, code / 255.0, 1.0);
}