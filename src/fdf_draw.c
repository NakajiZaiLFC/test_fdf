

#include "../includes/fdf.h"

void fdf_draw(t_fdf *fdf)
{
    int x;
    int y;
    int x0, y0, x1, y1;
    
    // 画像バッファをクリア
    ft_memset(fdf->img->addr, 0, fdf->map.width * fdf->map.height * (fdf->img->bpp / 8));

    y = 0;
    while (y < fdf->map.height)
    {
        x = 0;
        while (x < fdf->map.width)
        {
            x0 = x * 30;
            y0 = y * 30;
            iso_projection(&x0, &y0, fdf->map.points[y][x].z * 5);
            x0 += fdf->map.width / 2;
            y0 += fdf->map.height / 3;

            // 横方向の線を画像に描画
            if (x < fdf->map.width - 1)
            {
                x1 = (x + 1) * 30;
                y1 = y * 30;
                iso_projection(&x1, &y1, fdf->map.points[y][x + 1].z * 5);
                x1 += fdf->map.width / 2;
                y1 += fdf->map.height / 3;
                draw_line_to_image(fdf->img, (t_point){x0, y0}, (t_point){x1, y1}, 
                                 fdf->map.points[y][x].color);
            }

            // 縦方向の線を画像に描画
            if (y < fdf->map.height - 1)
            {
                x1 = x * 30;
                y1 = (y + 1) * 30;
                iso_projection(&x1, &y1, fdf->map.points[y + 1][x].z * 5);
                x1 += fdf->map.width / 2;
                y1 += fdf->map.height / 3;
                draw_line_to_image(fdf->img, (t_point){x0, y0}, (t_point){x1, y1}, 
                                 fdf->map.points[y][x].color);
            }
            x++;
        }
        y++;
    }
    // 完成した画像をウィンドウに表示
    mlx_put_image_to_window(fdf->mlx_ptr, fdf->win_ptr, fdf->img->img_ptr, 0, 0);
}
