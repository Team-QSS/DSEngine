cbuffer WorldMatrixBuffer
{
	float4x4 worldMatrix;
};

cbuffer OrthoMatrixBuffer
{
	float4x4 orthoMatrix; 
};

float4 main( float4 pos : POSITION ) : SV_POSITION
{
	pos = mul(pos, worldMatrix);
	pos = mul(pos, orthoMatrix);
	return pos;
}