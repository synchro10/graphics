#include "parser.h"

bool Parser::initEngine(const QString &fileName, GraphicEngine &engine)
{
    QFile file(fileName);
    if (!file.open(QIODevice::ReadOnly)){
        return false;
    }

    int n,m,k;
    float a,b,c,d;
    float zn,zf,sw,sh;
    float e11, e12, e13, e21, e22, e23, e31, e32, e33;
    int br, bg, bb;
    int K;
    int R,G,B;
    float cx, cy, cz;
    float r11, r12, r13, r21, r22, r23, r31, r32, r33;
    int N;
    float x, y;

    QTextStream in(&file);
    QString str = in.readLine();
    deleteComment(str);
    QStringList words = str.split(" ", QString::SkipEmptyParts);
    if (words.length() != 7){
        file.close();
        return false;
    }
    n = words.at(0).toInt();
    m = words.at(1).toInt();
    k = words.at(2).toInt();
    a = words.at(3).toFloat();
    b = words.at(4).toFloat();
    c = words.at(5).toFloat();
    d = words.at(6).toFloat();

    str = in.readLine();
    deleteComment(str);
    words = str.split(" ", QString::SkipEmptyParts);
    if (words.length() != 4){
        file.close();
        return false;
    }
    zn = words.at(0).toFloat();
    zf = words.at(1).toFloat();
    sw = words.at(2).toFloat();
    sh = words.at(3).toFloat();

    str = in.readLine();
    deleteComment(str);
    words = str.split(" ", QString::SkipEmptyParts);
    if (words.length() != 3){
        file.close();
        return false;
    }
    e11 = words.at(0).toFloat();
    e12 = words.at(1).toFloat();
    e13 = words.at(2).toFloat();

    str = in.readLine();
    deleteComment(str);
    words = str.split(" ", QString::SkipEmptyParts);
    if (words.length() != 3){
        file.close();
        return false;
    }
    e21 = words.at(0).toFloat();
    e22 = words.at(1).toFloat();
    e23 = words.at(2).toFloat();

    str = in.readLine();
    deleteComment(str);
    words = str.split(" ", QString::SkipEmptyParts);
    if (words.length() != 3){
        file.close();
        return false;
    }
    e31 = words.at(0).toFloat();
    e32 = words.at(1).toFloat();
    e33 = words.at(2).toFloat();

    str = in.readLine();
    deleteComment(str);
    words = str.split(" ", QString::SkipEmptyParts);
    if (words.length() != 3){
        file.close();
        return false;
    }
    br = words.at(0).toInt();
    bg = words.at(1).toInt();
    bb = words.at(2).toInt();

    str = in.readLine();
    deleteComment(str);
    words = str.split(" ", QString::SkipEmptyParts);
    if (words.length() != 1){
        file.close();
        return false;
    }
    K = words.at(0).toInt();

    Settings settings = Settings(n,m,k,a,b,c,d);

    for(int i = 0; i < K; i++){
        str = in.readLine();
        deleteComment(str);
        words = str.split(" ", QString::SkipEmptyParts);
        if (words.length() != 3){
            file.close();
            return false;
        }
        R = words.at(0).toInt();
        G = words.at(1).toInt();
        B = words.at(2).toInt();

        str = in.readLine();
        deleteComment(str);
        words = str.split(" ", QString::SkipEmptyParts);
        if (words.length() != 3){
            file.close();
            return false;
        }
        cx = words.at(0).toFloat();
        cy = words.at(1).toFloat();
        cz = words.at(2).toFloat();

        str = in.readLine();
        deleteComment(str);
        words = str.split(" ", QString::SkipEmptyParts);
        if (words.length() != 3){
            file.close();
            return false;
        }
        r11 = words.at(0).toFloat();
        r12 = words.at(1).toFloat();
        r13 = words.at(2).toFloat();

        str = in.readLine();
        deleteComment(str);
        words = str.split(" ", QString::SkipEmptyParts);
        if (words.length() != 3){
            file.close();
            return false;
        }
        r21 = words.at(0).toFloat();
        r22 = words.at(1).toFloat();
        r23 = words.at(2).toFloat();

        str = in.readLine();
        deleteComment(str);
        words = str.split(" ", QString::SkipEmptyParts);
        if (words.length() != 3){
            file.close();
            return false;
        }
        r31 = words.at(0).toFloat();
        r32 = words.at(1).toFloat();
        r33 = words.at(2).toFloat();

        str = in.readLine();
        deleteComment(str);
        words = str.split(" ", QString::SkipEmptyParts);
        if (words.length() != 1){
            file.close();
            return false;
        }
        N = words.at(0).toInt();

        BSpline bspline;
        for(int j = 0; j < N; j++){
            str = in.readLine();
            deleteComment(str);
            words = str.split(" ", QString::SkipEmptyParts);
            if (words.length() != 2){
                file.close();
                return false;
            }
            x = words.at(0).toFloat();
            y = words.at(1).toFloat();
            bspline.addPoint(x,y);
            if (j == 0 || j == N - 1){
                bspline.addPoint(x,y);
                bspline.addPoint(x,y);
            }
        }
        bspline.createValues();
        Object object;
        object.setColor(qRgb(R,G,B));
        object.moveTo(cx, cy, cz);
        object.setBSpline(bspline);
        object.setGlobalRotate(QMatrix4x4(r11, r12, r13, 0,
                                          r21, r22, r23, 0,
                                          r31, r32, r33, 0,
                                          0,0,0,1));
        engine.addObject(object);
    }
    engine.setSettings(settings);
    engine.setDefaultFontColor(qRgb(br,bg,bb));
    engine.setGlobalRotate(QMatrix4x4(e11, e12, e13, 0,
                                      e21, e22, e23, 0,
                                      e31, e32, e33, 0,
                                      0,0,0,1));

    file.close();
    return true;
}
