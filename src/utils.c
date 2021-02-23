#include "scop.h"

double min(double a, double b)
{
    return ((a < b) ? a : b);
}

double max(double a, double b)
{
    return ((a > b) ? a : b);
}

double clamp(double a, double mi, double ma)
{
    return (min(max(a, mi), ma));
}

t_mat4 v_add(t_mat4 mat, t_vec3 v2)
{
    return ((t_mat4){mat.mat[0][0] + v2.x, mat.mat[0][1] + v2.y, mat.mat[0][2] + v2.z, mat.mat[0][3],
                     mat.mat[1][0] + v2.x, mat.mat[1][1] + v2.y, mat.mat[1][2] + v2.z, mat.mat[1][3],
                     mat.mat[2][0] + v2.x, mat.mat[2][1] + v2.y, mat.mat[2][2] + v2.z, mat.mat[2][3],
                     mat.mat[3][0], mat.mat[3][1], mat.mat[3][2], mat.mat[3][3]});
}

// GLfloat *flat_matrice(t_mat4 mat)
// {
//     GLfloat flat[16];
//     int n = 0;
//     int i = -1;
//     while (++i < 4)
//     {
//         int j = -1;
//         while (++j < 4)
//         {
//             flat[n] = mat.mat[i][j];
//             n++;
//         }
//     }
//     return flat;
// }
//
// t_mat4 v_sub(t_mat4 v1, t_mat4 v2)
// {
// return ((t_mat4){v1.x - v2.x, v1.y - v2.y, v1.z - v2.z});
// }
//
// t_mat4 v_mul(t_mat4 v1, t_mat4 v2)
// {
// return ((t_mat4){v1.x * v2.x, v1.y * v2.y, v1.z * v2.z});
// }
//
// t_mat4 v_mulk(t_mat4 v1, double k)
// {
// return ((t_mat4){v1.x * k, v1.y * k, v1.z * k});
// }
// t_mat4 v_div(t_mat4 v1, double k)
// {
// return ((t_mat4){v1.x / k, v1.y / k, v1.z / k});
// }

// t_mat4	vrot(t_mat4 in, t_mat4 angle)
// {
// 	t_mat4		rx;
// 	t_mat4		ry;
// 	t_mat4		rz;
// 	t_mat4		vcos;
// 	t_mat4		vsin;

// 	angle.x *= M_PI / 180;
// 	angle.y *= M_PI / 180;
// 	angle.z *= M_PI / 180;
// 	vcos = (t_mat4){cos(angle.z), cos(angle.y), cos(angle.z)};
// 	vsin = (t_mat4){sin(angle.z), sin(angle.y), sin(angle.z)};
// 	rx.x = in.x;
// 	rx.y = in.y * vcos.x + in.z * -vsin.x;
// 	rx.z = in.y * vsin.x + in.z * vcos.x;
// 	ry.x = rx.x * vcos.y + rx.z * vsin.y;
// 	ry.y = rx.y;
// 	ry.z = rx.x * -vsin.y + in.z * vcos.x;
// 	rz.x = ry.x * vcos.z + ry.y * -vsin.z;
// 	rz.y = ry.x * vsin.z + ry.y * vcos.z;
// 	rz.z = ry.z;
// 	return (rz);
// }
// void rot_x(t_param *p, t_mat4 *d)
// {
//     t_mat4 new;

//     new.x = d->x;
//     new.y = d->y *cosf(p->cam.rot.x) - d->z *sinf(p->cam.rot.x);
//     new.z = d->y *sinf(p->cam.rot.x) + d->z *cosf(p->cam.rot.x);
//     *d = new;
// }

// void rot_y(t_param *p, t_mat4 *d)
// {
//     t_mat4 new;

//     new.x = d->x *cosf(p->cam.rot.y) + d->z *sinf(p->cam.rot.y);
//     new.y = d->y;
//     new.z = d->x * -sinf(p->cam.rot.y) + d->z *cosf(p->cam.rot.y);
//     *d = new;
// }

// double v_dotproduct(t_mat4 v1, t_mat4 v2)
// {
//     return (v1.x * v2.x + v1.y * v2.y + v1.z * v2.z);
// }

// double v_length(t_mat4 v)
// {
//     return (sqrtf(v_dotproduct(v, v)));
// }

// t_mat4 v_normalize(t_mat4 v)
// {
//     double l = v_length(v);
//     return ((t_mat4){v.x / l, v.y / l, v.z / l});
// }

// t_mat4 v_crossprod(t_mat4 v1, t_mat4 v2)
// {
//     t_mat4 v;

//     v.x = v1.y * v2.z - v1.z * v2.y;
//     v.y = v1.z * v2.x - v1.x * v2.z;
//     v.z = v1.x * v2.y - v1.y * v2.x;
//     return (v);
// }

void init_mat4(t_mat4 *s)
{
    int i = -1;
    while (++i < 4)
    {
        int j = -1;
        while (++j < 4)
        {
            s->mat[i][j] = 0.0f;
        }
    }
    s->mat[0][0] = 1.0f;
    s->mat[1][1] = 1.0f;
    s->mat[2][2] = 1.0f;
    s->mat[3][3] = 1.0f;
}
