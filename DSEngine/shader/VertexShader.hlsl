cbuffer WorldMatrixBuffer
{
	float4x4 worldMatrix;
};

float4 main( float4 pos : POSITION ) : SV_POSITION
{
	return mul(pos, worldMatrix);
}