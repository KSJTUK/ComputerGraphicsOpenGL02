#version 330 core
//--- out_Color: ���ؽ� ���̴����� �Է¹޴� ���� ��
//--- FragColor: ����� ������ ������ ������ ���۷� ���� ��.

uniform vec3 objectColor; //--- ���ؽ� ���̴����Լ� ���� ����

out vec4 FragColor; //--- ���� ���

void main(void)
{
	FragColor = vec4 (objectColor, 1.0);
}