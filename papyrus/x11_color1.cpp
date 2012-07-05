/***************************************************************************
 *   Copyright (C) 2006 by Rick L. Vinyard, Jr.                            *
 *   rvinyard@cs.nmsu.edu                                                  *
 *                                                                         *
 *   This file is part of the papyrus library.                             *
 *                                                                         *
 *   papyrus is free software; you can redistribute it and/or modify       *
 *   it under the terms of the GNU Lesser General Public License           *
 *   version 3.0 as published by the Free Software Foundation.             *
 *                                                                         *
 *   papyrus is distributed in the hope that it will be useful,            *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU Lesser General Public License version 3.0 for more details.       *
 *                                                                         *
 *   You should have received a copy of the GNU Lesser General Public      *
 *   License along with the papyrus library. If not, see                   *
 *   <http://www.gnu.org/licenses/>.                                       *
 ***************************************************************************/
#include "x11_color.h"

#include <papyrus/rgba.h>

namespace Papyrus
{

  void x11_colors_1( X11Colors& colors )
  {
    colors["snow"] = RGBA( 1, 0.980392156862745, 0.980392156862745 );
    colors["ghost white"] = RGBA( 0.972549019607843, 0.972549019607843, 1 );
    colors["GhostWhite"] = RGBA( 0.972549019607843, 0.972549019607843, 1 );
    colors["white smoke"] = RGBA( 0.96078431372549, 0.96078431372549, 0.96078431372549 );
    colors["WhiteSmoke"] = RGBA( 0.96078431372549, 0.96078431372549, 0.96078431372549 );
    colors["gainsboro"] = RGBA( 0.862745098039216, 0.862745098039216, 0.862745098039216 );
    colors["floral white"] = RGBA( 1, 0.980392156862745, 0.941176470588235 );
    colors["FloralWhite"] = RGBA( 1, 0.980392156862745, 0.941176470588235 );
    colors["old lace"] = RGBA( 0.992156862745098, 0.96078431372549, 0.901960784313726 );
    colors["OldLace"] = RGBA( 0.992156862745098, 0.96078431372549, 0.901960784313726 );
    colors["linen"] = RGBA( 0.980392156862745, 0.941176470588235, 0.901960784313726 );
    colors["antique white"] = RGBA( 0.980392156862745, 0.92156862745098, 0.843137254901961 );
    colors["AntiqueWhite"] = RGBA( 0.980392156862745, 0.92156862745098, 0.843137254901961 );
    colors["papaya whip"] = RGBA( 1, 0.937254901960784, 0.835294117647059 );
    colors["PapayaWhip"] = RGBA( 1, 0.937254901960784, 0.835294117647059 );
    colors["blanched almond"] = RGBA( 1, 0.92156862745098, 0.803921568627451 );
    colors["BlanchedAlmond"] = RGBA( 1, 0.92156862745098, 0.803921568627451 );
    colors["bisque"] = RGBA( 1, 0.894117647058824, 0.768627450980392 );
    colors["peach puff"] = RGBA( 1, 0.854901960784314, 0.725490196078431 );
    colors["PeachPuff"] = RGBA( 1, 0.854901960784314, 0.725490196078431 );
    colors["navajo white"] = RGBA( 1, 0.870588235294118, 0.67843137254902 );
    colors["NavajoWhite"] = RGBA( 1, 0.870588235294118, 0.67843137254902 );
    colors["moccasin"] = RGBA( 1, 0.894117647058824, 0.709803921568627 );
    colors["cornsilk"] = RGBA( 1, 0.972549019607843, 0.862745098039216 );
    colors["ivory"] = RGBA( 1, 1, 0.941176470588235 );
    colors["lemon chiffon"] = RGBA( 1, 0.980392156862745, 0.803921568627451 );
    colors["LemonChiffon"] = RGBA( 1, 0.980392156862745, 0.803921568627451 );
    colors["seashell"] = RGBA( 1, 0.96078431372549, 0.933333333333333 );
    colors["honeydew"] = RGBA( 0.941176470588235, 1, 0.941176470588235 );
    colors["mint cream"] = RGBA( 0.96078431372549, 1, 0.980392156862745 );
    colors["MintCream"] = RGBA( 0.96078431372549, 1, 0.980392156862745 );
    colors["azure"] = RGBA( 0.941176470588235, 1, 1 );
    colors["alice blue"] = RGBA( 0.941176470588235, 0.972549019607843, 1 );
    colors["AliceBlue"] = RGBA( 0.941176470588235, 0.972549019607843, 1 );
    colors["lavender"] = RGBA( 0.901960784313726, 0.901960784313726, 0.980392156862745 );
    colors["lavender blush"] = RGBA( 1, 0.941176470588235, 0.96078431372549 );
    colors["LavenderBlush"] = RGBA( 1, 0.941176470588235, 0.96078431372549 );
    colors["misty rose"] = RGBA( 1, 0.894117647058824, 0.882352941176471 );
    colors["MistyRose"] = RGBA( 1, 0.894117647058824, 0.882352941176471 );
    colors["white"] = RGBA( 1, 1, 1 );
    colors["black"] = RGBA( 0, 0, 0 );
    colors["dark slate gray"] = RGBA( 0.184313725490196, 0.309803921568627, 0.309803921568627 );
    colors["DarkSlateGray"] = RGBA( 0.184313725490196, 0.309803921568627, 0.309803921568627 );
    colors["dark slate grey"] = RGBA( 0.184313725490196, 0.309803921568627, 0.309803921568627 );
    colors["DarkSlateGrey"] = RGBA( 0.184313725490196, 0.309803921568627, 0.309803921568627 );
    colors["dim gray"] = RGBA( 0.411764705882353, 0.411764705882353, 0.411764705882353 );
    colors["DimGray"] = RGBA( 0.411764705882353, 0.411764705882353, 0.411764705882353 );
    colors["dim grey"] = RGBA( 0.411764705882353, 0.411764705882353, 0.411764705882353 );
    colors["DimGrey"] = RGBA( 0.411764705882353, 0.411764705882353, 0.411764705882353 );
    colors["slate gray"] = RGBA( 0.43921568627451, 0.501960784313725, 0.564705882352941 );
    colors["SlateGray"] = RGBA( 0.43921568627451, 0.501960784313725, 0.564705882352941 );
    colors["slate grey"] = RGBA( 0.43921568627451, 0.501960784313725, 0.564705882352941 );
    colors["SlateGrey"] = RGBA( 0.43921568627451, 0.501960784313725, 0.564705882352941 );
    colors["light slate gray"] = RGBA( 0.466666666666667, 0.533333333333333, 0.6 );
    colors["LightSlateGray"] = RGBA( 0.466666666666667, 0.533333333333333, 0.6 );
    colors["light slate grey"] = RGBA( 0.466666666666667, 0.533333333333333, 0.6 );
    colors["LightSlateGrey"] = RGBA( 0.466666666666667, 0.533333333333333, 0.6 );
    colors["gray"] = RGBA( 0.745098039215686, 0.745098039215686, 0.745098039215686 );
    colors["grey"] = RGBA( 0.745098039215686, 0.745098039215686, 0.745098039215686 );
    colors["light grey"] = RGBA( 0.827450980392157, 0.827450980392157, 0.827450980392157 );
    colors["LightGrey"] = RGBA( 0.827450980392157, 0.827450980392157, 0.827450980392157 );
    colors["light gray"] = RGBA( 0.827450980392157, 0.827450980392157, 0.827450980392157 );
    colors["LightGray"] = RGBA( 0.827450980392157, 0.827450980392157, 0.827450980392157 );
    colors["midnight blue"] = RGBA( 0.0980392156862745, 0.0980392156862745, 0.43921568627451 );
    colors["MidnightBlue"] = RGBA( 0.0980392156862745, 0.0980392156862745, 0.43921568627451 );
    colors["navy"] = RGBA( 0, 0, 0.501960784313725 );
    colors["navy blue"] = RGBA( 0, 0, 0.501960784313725 );
    colors["NavyBlue"] = RGBA( 0, 0, 0.501960784313725 );
    colors["cornflower blue"] = RGBA( 0.392156862745098, 0.584313725490196, 0.929411764705882 );
    colors["CornflowerBlue"] = RGBA( 0.392156862745098, 0.584313725490196, 0.929411764705882 );
    colors["dark slate blue"] = RGBA( 0.282352941176471, 0.23921568627451, 0.545098039215686 );
    colors["DarkSlateBlue"] = RGBA( 0.282352941176471, 0.23921568627451, 0.545098039215686 );
    colors["slate blue"] = RGBA( 0.415686274509804, 0.352941176470588, 0.803921568627451 );
    colors["SlateBlue"] = RGBA( 0.415686274509804, 0.352941176470588, 0.803921568627451 );
    colors["medium slate blue"] = RGBA( 0.482352941176471, 0.407843137254902, 0.933333333333333 );
    colors["MediumSlateBlue"] = RGBA( 0.482352941176471, 0.407843137254902, 0.933333333333333 );
    colors["light slate blue"] = RGBA( 0.517647058823529, 0.43921568627451, 1 );
    colors["LightSlateBlue"] = RGBA( 0.517647058823529, 0.43921568627451, 1 );
    colors["medium blue"] = RGBA( 0, 0, 0.803921568627451 );
    colors["MediumBlue"] = RGBA( 0, 0, 0.803921568627451 );
    colors["royal blue"] = RGBA( 0.254901960784314, 0.411764705882353, 0.882352941176471 );
    colors["RoyalBlue"] = RGBA( 0.254901960784314, 0.411764705882353, 0.882352941176471 );
    colors["blue"] = RGBA( 0, 0, 1 );
    colors["dodger blue"] = RGBA( 0.117647058823529, 0.564705882352941, 1 );
    colors["DodgerBlue"] = RGBA( 0.117647058823529, 0.564705882352941, 1 );
    colors["deep sky blue"] = RGBA( 0, 0.749019607843137, 1 );
    colors["DeepSkyBlue"] = RGBA( 0, 0.749019607843137, 1 );
    colors["sky blue"] = RGBA( 0.529411764705882, 0.807843137254902, 0.92156862745098 );
    colors["SkyBlue"] = RGBA( 0.529411764705882, 0.807843137254902, 0.92156862745098 );
    colors["light sky blue"] = RGBA( 0.529411764705882, 0.807843137254902, 0.980392156862745 );
    colors["LightSkyBlue"] = RGBA( 0.529411764705882, 0.807843137254902, 0.980392156862745 );
    colors["steel blue"] = RGBA( 0.274509803921569, 0.509803921568627, 0.705882352941177 );
    colors["SteelBlue"] = RGBA( 0.274509803921569, 0.509803921568627, 0.705882352941177 );
    colors["light steel blue"] = RGBA( 0.690196078431373, 0.768627450980392, 0.870588235294118 );
    colors["LightSteelBlue"] = RGBA( 0.690196078431373, 0.768627450980392, 0.870588235294118 );
    colors["light blue"] = RGBA( 0.67843137254902, 0.847058823529412, 0.901960784313726 );
    colors["LightBlue"] = RGBA( 0.67843137254902, 0.847058823529412, 0.901960784313726 );
    colors["powder blue"] = RGBA( 0.690196078431373, 0.87843137254902, 0.901960784313726 );
    colors["PowderBlue"] = RGBA( 0.690196078431373, 0.87843137254902, 0.901960784313726 );
    colors["pale turquoise"] = RGBA( 0.686274509803922, 0.933333333333333, 0.933333333333333 );
    colors["PaleTurquoise"] = RGBA( 0.686274509803922, 0.933333333333333, 0.933333333333333 );
    colors["dark turquoise"] = RGBA( 0, 0.807843137254902, 0.819607843137255 );
    colors["DarkTurquoise"] = RGBA( 0, 0.807843137254902, 0.819607843137255 );
    colors["medium turquoise"] = RGBA( 0.282352941176471, 0.819607843137255, 0.8 );
    colors["MediumTurquoise"] = RGBA( 0.282352941176471, 0.819607843137255, 0.8 );
    colors["turquoise"] = RGBA( 0.250980392156863, 0.87843137254902, 0.815686274509804 );
    colors["cyan"] = RGBA( 0, 1, 1 );
    colors["light cyan"] = RGBA( 0.87843137254902, 1, 1 );
    colors["LightCyan"] = RGBA( 0.87843137254902, 1, 1 );
    colors["cadet blue"] = RGBA( 0.372549019607843, 0.619607843137255, 0.627450980392157 );
    colors["CadetBlue"] = RGBA( 0.372549019607843, 0.619607843137255, 0.627450980392157 );
    colors["medium aquamarine"] = RGBA( 0.4, 0.803921568627451, 0.666666666666667 );
    colors["MediumAquamarine"] = RGBA( 0.4, 0.803921568627451, 0.666666666666667 );
    colors["aquamarine"] = RGBA( 0.498039215686275, 1, 0.831372549019608 );
    colors["dark green"] = RGBA( 0, 0.392156862745098, 0 );
    colors["DarkGreen"] = RGBA( 0, 0.392156862745098, 0 );
    colors["dark olive green"] = RGBA( 0.333333333333333, 0.419607843137255, 0.184313725490196 );
    colors["DarkOliveGreen"] = RGBA( 0.333333333333333, 0.419607843137255, 0.184313725490196 );
    colors["dark sea green"] = RGBA( 0.56078431372549, 0.737254901960784, 0.56078431372549 );
    colors["DarkSeaGreen"] = RGBA( 0.56078431372549, 0.737254901960784, 0.56078431372549 );
    colors["sea green"] = RGBA( 0.180392156862745, 0.545098039215686, 0.341176470588235 );
    colors["SeaGreen"] = RGBA( 0.180392156862745, 0.545098039215686, 0.341176470588235 );
    colors["medium sea green"] = RGBA( 0.235294117647059, 0.701960784313725, 0.443137254901961 );
    colors["MediumSeaGreen"] = RGBA( 0.235294117647059, 0.701960784313725, 0.443137254901961 );
    colors["light sea green"] = RGBA( 0.125490196078431, 0.698039215686274, 0.666666666666667 );
    colors["LightSeaGreen"] = RGBA( 0.125490196078431, 0.698039215686274, 0.666666666666667 );
    colors["pale green"] = RGBA( 0.596078431372549, 0.984313725490196, 0.596078431372549 );
    colors["PaleGreen"] = RGBA( 0.596078431372549, 0.984313725490196, 0.596078431372549 );
    colors["spring green"] = RGBA( 0, 1, 0.498039215686275 );
    colors["SpringGreen"] = RGBA( 0, 1, 0.498039215686275 );
    colors["lawn green"] = RGBA( 0.486274509803922, 0.988235294117647, 0 );
    colors["LawnGreen"] = RGBA( 0.486274509803922, 0.988235294117647, 0 );
    colors["green"] = RGBA( 0, 1, 0 );
    colors["chartreuse"] = RGBA( 0.498039215686275, 1, 0 );
    colors["medium spring green"] = RGBA( 0, 0.980392156862745, 0.603921568627451 );
    colors["MediumSpringGreen"] = RGBA( 0, 0.980392156862745, 0.603921568627451 );
    colors["green yellow"] = RGBA( 0.67843137254902, 1, 0.184313725490196 );
    colors["GreenYellow"] = RGBA( 0.67843137254902, 1, 0.184313725490196 );
    colors["lime green"] = RGBA( 0.196078431372549, 0.803921568627451, 0.196078431372549 );
    colors["LimeGreen"] = RGBA( 0.196078431372549, 0.803921568627451, 0.196078431372549 );
    colors["yellow green"] = RGBA( 0.603921568627451, 0.803921568627451, 0.196078431372549 );
    colors["YellowGreen"] = RGBA( 0.603921568627451, 0.803921568627451, 0.196078431372549 );
    colors["forest green"] = RGBA( 0.133333333333333, 0.545098039215686, 0.133333333333333 );
    colors["ForestGreen"] = RGBA( 0.133333333333333, 0.545098039215686, 0.133333333333333 );
    colors["olive drab"] = RGBA( 0.419607843137255, 0.556862745098039, 0.137254901960784 );
    colors["OliveDrab"] = RGBA( 0.419607843137255, 0.556862745098039, 0.137254901960784 );
    colors["dark khaki"] = RGBA( 0.741176470588235, 0.717647058823529, 0.419607843137255 );
    colors["DarkKhaki"] = RGBA( 0.741176470588235, 0.717647058823529, 0.419607843137255 );
    colors["khaki"] = RGBA( 0.941176470588235, 0.901960784313726, 0.549019607843137 );
    colors["pale goldenrod"] = RGBA( 0.933333333333333, 0.909803921568627, 0.666666666666667 );
    colors["PaleGoldenrod"] = RGBA( 0.933333333333333, 0.909803921568627, 0.666666666666667 );
    colors["light goldenrod yellow"] = RGBA( 0.980392156862745, 0.980392156862745, 0.823529411764706 );
    colors["LightGoldenrodYellow"] = RGBA( 0.980392156862745, 0.980392156862745, 0.823529411764706 );
    colors["light yellow"] = RGBA( 1, 1, 0.87843137254902 );
    colors["LightYellow"] = RGBA( 1, 1, 0.87843137254902 );
    colors["yellow"] = RGBA( 1, 1, 0 );
    colors["gold"] = RGBA( 1, 0.843137254901961, 0 );
    colors["light goldenrod"] = RGBA( 0.933333333333333, 0.866666666666667, 0.509803921568627 );
    colors["LightGoldenrod"] = RGBA( 0.933333333333333, 0.866666666666667, 0.509803921568627 );
    colors["goldenrod"] = RGBA( 0.854901960784314, 0.647058823529412, 0.125490196078431 );
    colors["dark goldenrod"] = RGBA( 0.72156862745098, 0.525490196078431, 0.0431372549019608 );
    colors["DarkGoldenrod"] = RGBA( 0.72156862745098, 0.525490196078431, 0.0431372549019608 );
    colors["rosy brown"] = RGBA( 0.737254901960784, 0.56078431372549, 0.56078431372549 );
    colors["RosyBrown"] = RGBA( 0.737254901960784, 0.56078431372549, 0.56078431372549 );
    colors["indian red"] = RGBA( 0.803921568627451, 0.36078431372549, 0.36078431372549 );
    colors["IndianRed"] = RGBA( 0.803921568627451, 0.36078431372549, 0.36078431372549 );
    colors["saddle brown"] = RGBA( 0.545098039215686, 0.270588235294118, 0.0745098039215686 );
    colors["SaddleBrown"] = RGBA( 0.545098039215686, 0.270588235294118, 0.0745098039215686 );
    colors["sienna"] = RGBA( 0.627450980392157, 0.32156862745098, 0.176470588235294 );
    colors["peru"] = RGBA( 0.803921568627451, 0.52156862745098, 0.247058823529412 );
    colors["burlywood"] = RGBA( 0.870588235294118, 0.72156862745098, 0.529411764705882 );
    colors["beige"] = RGBA( 0.96078431372549, 0.96078431372549, 0.862745098039216 );
    colors["wheat"] = RGBA( 0.96078431372549, 0.870588235294118, 0.701960784313725 );
    colors["sandy brown"] = RGBA( 0.956862745098039, 0.643137254901961, 0.376470588235294 );
    colors["SandyBrown"] = RGBA( 0.956862745098039, 0.643137254901961, 0.376470588235294 );
    colors["tan"] = RGBA( 0.823529411764706, 0.705882352941177, 0.549019607843137 );
    colors["chocolate"] = RGBA( 0.823529411764706, 0.411764705882353, 0.117647058823529 );
    colors["firebrick"] = RGBA( 0.698039215686274, 0.133333333333333, 0.133333333333333 );
    colors["brown"] = RGBA( 0.647058823529412, 0.164705882352941, 0.164705882352941 );
    colors["dark salmon"] = RGBA( 0.913725490196078, 0.588235294117647, 0.47843137254902 );
    colors["DarkSalmon"] = RGBA( 0.913725490196078, 0.588235294117647, 0.47843137254902 );
    colors["salmon"] = RGBA( 0.980392156862745, 0.501960784313725, 0.447058823529412 );
    colors["light salmon"] = RGBA( 1, 0.627450980392157, 0.47843137254902 );
    colors["LightSalmon"] = RGBA( 1, 0.627450980392157, 0.47843137254902 );
    colors["orange"] = RGBA( 1, 0.647058823529412, 0 );
    colors["dark orange"] = RGBA( 1, 0.549019607843137, 0 );
    colors["DarkOrange"] = RGBA( 1, 0.549019607843137, 0 );
    colors["coral"] = RGBA( 1, 0.498039215686275, 0.313725490196078 );
    colors["light coral"] = RGBA( 0.941176470588235, 0.501960784313725, 0.501960784313725 );
    colors["LightCoral"] = RGBA( 0.941176470588235, 0.501960784313725, 0.501960784313725 );
    colors["tomato"] = RGBA( 1, 0.388235294117647, 0.27843137254902 );
    colors["orange red"] = RGBA( 1, 0.270588235294118, 0 );
    colors["OrangeRed"] = RGBA( 1, 0.270588235294118, 0 );
  }

}
