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

  void x11_colors_3( X11Colors& colors )
  {
    colors["khaki1"] = RGBA( 1, 0.964705882352941, 0.56078431372549 );
    colors["khaki2"] = RGBA( 0.933333333333333, 0.901960784313726, 0.52156862745098 );
    colors["khaki3"] = RGBA( 0.803921568627451, 0.776470588235294, 0.450980392156863 );
    colors["khaki4"] = RGBA( 0.545098039215686, 0.525490196078431, 0.305882352941176 );
    colors["LightGoldenrod1"] = RGBA( 1, 0.925490196078431, 0.545098039215686 );
    colors["LightGoldenrod2"] = RGBA( 0.933333333333333, 0.862745098039216, 0.509803921568627 );
    colors["LightGoldenrod3"] = RGBA( 0.803921568627451, 0.745098039215686, 0.43921568627451 );
    colors["LightGoldenrod4"] = RGBA( 0.545098039215686, 0.505882352941176, 0.298039215686275 );
    colors["LightYellow1"] = RGBA( 1, 1, 0.87843137254902 );
    colors["LightYellow2"] = RGBA( 0.933333333333333, 0.933333333333333, 0.819607843137255 );
    colors["LightYellow3"] = RGBA( 0.803921568627451, 0.803921568627451, 0.705882352941177 );
    colors["LightYellow4"] = RGBA( 0.545098039215686, 0.545098039215686, 0.47843137254902 );
    colors["yellow1"] = RGBA( 1, 1, 0 );
    colors["yellow2"] = RGBA( 0.933333333333333, 0.933333333333333, 0 );
    colors["yellow3"] = RGBA( 0.803921568627451, 0.803921568627451, 0 );
    colors["yellow4"] = RGBA( 0.545098039215686, 0.545098039215686, 0 );
    colors["gold1"] = RGBA( 1, 0.843137254901961, 0 );
    colors["gold2"] = RGBA( 0.933333333333333, 0.788235294117647, 0 );
    colors["gold3"] = RGBA( 0.803921568627451, 0.67843137254902, 0 );
    colors["gold4"] = RGBA( 0.545098039215686, 0.458823529411765, 0 );
    colors["goldenrod1"] = RGBA( 1, 0.756862745098039, 0.145098039215686 );
    colors["goldenrod2"] = RGBA( 0.933333333333333, 0.705882352941177, 0.133333333333333 );
    colors["goldenrod3"] = RGBA( 0.803921568627451, 0.607843137254902, 0.113725490196078 );
    colors["goldenrod4"] = RGBA( 0.545098039215686, 0.411764705882353, 0.0784313725490196 );
    colors["DarkGoldenrod1"] = RGBA( 1, 0.725490196078431, 0.0588235294117647 );
    colors["DarkGoldenrod2"] = RGBA( 0.933333333333333, 0.67843137254902, 0.0549019607843137 );
    colors["DarkGoldenrod3"] = RGBA( 0.803921568627451, 0.584313725490196, 0.0470588235294118 );
    colors["DarkGoldenrod4"] = RGBA( 0.545098039215686, 0.396078431372549, 0.0313725490196078 );
    colors["RosyBrown1"] = RGBA( 1, 0.756862745098039, 0.756862745098039 );
    colors["RosyBrown2"] = RGBA( 0.933333333333333, 0.705882352941177, 0.705882352941177 );
    colors["RosyBrown3"] = RGBA( 0.803921568627451, 0.607843137254902, 0.607843137254902 );
    colors["RosyBrown4"] = RGBA( 0.545098039215686, 0.411764705882353, 0.411764705882353 );
    colors["IndianRed1"] = RGBA( 1, 0.415686274509804, 0.415686274509804 );
    colors["IndianRed2"] = RGBA( 0.933333333333333, 0.388235294117647, 0.388235294117647 );
    colors["IndianRed3"] = RGBA( 0.803921568627451, 0.333333333333333, 0.333333333333333 );
    colors["IndianRed4"] = RGBA( 0.545098039215686, 0.227450980392157, 0.227450980392157 );
    colors["sienna1"] = RGBA( 1, 0.509803921568627, 0.27843137254902 );
    colors["sienna2"] = RGBA( 0.933333333333333, 0.474509803921569, 0.258823529411765 );
    colors["sienna3"] = RGBA( 0.803921568627451, 0.407843137254902, 0.223529411764706 );
    colors["sienna4"] = RGBA( 0.545098039215686, 0.27843137254902, 0.149019607843137 );
    colors["burlywood1"] = RGBA( 1, 0.827450980392157, 0.607843137254902 );
    colors["burlywood2"] = RGBA( 0.933333333333333, 0.772549019607843, 0.568627450980392 );
    colors["burlywood3"] = RGBA( 0.803921568627451, 0.666666666666667, 0.490196078431373 );
    colors["burlywood4"] = RGBA( 0.545098039215686, 0.450980392156863, 0.333333333333333 );
    colors["wheat1"] = RGBA( 1, 0.905882352941176, 0.729411764705882 );
    colors["wheat2"] = RGBA( 0.933333333333333, 0.847058823529412, 0.682352941176471 );
    colors["wheat3"] = RGBA( 0.803921568627451, 0.729411764705882, 0.588235294117647 );
    colors["wheat4"] = RGBA( 0.545098039215686, 0.494117647058824, 0.4 );
    colors["tan1"] = RGBA( 1, 0.647058823529412, 0.309803921568627 );
    colors["tan2"] = RGBA( 0.933333333333333, 0.603921568627451, 0.286274509803922 );
    colors["tan3"] = RGBA( 0.803921568627451, 0.52156862745098, 0.247058823529412 );
    colors["tan4"] = RGBA( 0.545098039215686, 0.352941176470588, 0.168627450980392 );
    colors["chocolate1"] = RGBA( 1, 0.498039215686275, 0.141176470588235 );
    colors["chocolate2"] = RGBA( 0.933333333333333, 0.462745098039216, 0.129411764705882 );
    colors["chocolate3"] = RGBA( 0.803921568627451, 0.4, 0.113725490196078 );
    colors["chocolate4"] = RGBA( 0.545098039215686, 0.270588235294118, 0.0745098039215686 );
    colors["firebrick1"] = RGBA( 1, 0.188235294117647, 0.188235294117647 );
    colors["firebrick2"] = RGBA( 0.933333333333333, 0.172549019607843, 0.172549019607843 );
    colors["firebrick3"] = RGBA( 0.803921568627451, 0.149019607843137, 0.149019607843137 );
    colors["firebrick4"] = RGBA( 0.545098039215686, 0.101960784313725, 0.101960784313725 );
    colors["brown1"] = RGBA( 1, 0.250980392156863, 0.250980392156863 );
    colors["brown2"] = RGBA( 0.933333333333333, 0.231372549019608, 0.231372549019608 );
    colors["brown3"] = RGBA( 0.803921568627451, 0.2, 0.2 );
    colors["brown4"] = RGBA( 0.545098039215686, 0.137254901960784, 0.137254901960784 );
    colors["salmon1"] = RGBA( 1, 0.549019607843137, 0.411764705882353 );
    colors["salmon2"] = RGBA( 0.933333333333333, 0.509803921568627, 0.384313725490196 );
    colors["salmon3"] = RGBA( 0.803921568627451, 0.43921568627451, 0.329411764705882 );
    colors["salmon4"] = RGBA( 0.545098039215686, 0.298039215686275, 0.223529411764706 );
    colors["LightSalmon1"] = RGBA( 1, 0.627450980392157, 0.47843137254902 );
    colors["LightSalmon2"] = RGBA( 0.933333333333333, 0.584313725490196, 0.447058823529412 );
    colors["LightSalmon3"] = RGBA( 0.803921568627451, 0.505882352941176, 0.384313725490196 );
    colors["LightSalmon4"] = RGBA( 0.545098039215686, 0.341176470588235, 0.258823529411765 );
    colors["orange1"] = RGBA( 1, 0.647058823529412, 0 );
    colors["orange2"] = RGBA( 0.933333333333333, 0.603921568627451, 0 );
    colors["orange3"] = RGBA( 0.803921568627451, 0.52156862745098, 0 );
    colors["orange4"] = RGBA( 0.545098039215686, 0.352941176470588, 0 );
    colors["DarkOrange1"] = RGBA( 1, 0.498039215686275, 0 );
    colors["DarkOrange2"] = RGBA( 0.933333333333333, 0.462745098039216, 0 );
    colors["DarkOrange3"] = RGBA( 0.803921568627451, 0.4, 0 );
    colors["DarkOrange4"] = RGBA( 0.545098039215686, 0.270588235294118, 0 );
    colors["coral1"] = RGBA( 1, 0.447058823529412, 0.337254901960784 );
    colors["coral2"] = RGBA( 0.933333333333333, 0.415686274509804, 0.313725490196078 );
    colors["coral3"] = RGBA( 0.803921568627451, 0.356862745098039, 0.270588235294118 );
    colors["coral4"] = RGBA( 0.545098039215686, 0.243137254901961, 0.184313725490196 );
    colors["tomato1"] = RGBA( 1, 0.388235294117647, 0.27843137254902 );
    colors["tomato2"] = RGBA( 0.933333333333333, 0.36078431372549, 0.258823529411765 );
    colors["tomato3"] = RGBA( 0.803921568627451, 0.309803921568627, 0.223529411764706 );
    colors["tomato4"] = RGBA( 0.545098039215686, 0.211764705882353, 0.149019607843137 );
    colors["OrangeRed1"] = RGBA( 1, 0.270588235294118, 0 );
    colors["OrangeRed2"] = RGBA( 0.933333333333333, 0.250980392156863, 0 );
    colors["OrangeRed3"] = RGBA( 0.803921568627451, 0.215686274509804, 0 );
    colors["OrangeRed4"] = RGBA( 0.545098039215686, 0.145098039215686, 0 );
    colors["red1"] = RGBA( 1, 0, 0 );
    colors["red2"] = RGBA( 0.933333333333333, 0, 0 );
    colors["red3"] = RGBA( 0.803921568627451, 0, 0 );
    colors["red4"] = RGBA( 0.545098039215686, 0, 0 );
    colors["DeepPink1"] = RGBA( 1, 0.0784313725490196, 0.576470588235294 );
    colors["DeepPink2"] = RGBA( 0.933333333333333, 0.0705882352941176, 0.537254901960784 );
    colors["DeepPink3"] = RGBA( 0.803921568627451, 0.0627450980392157, 0.462745098039216 );
    colors["DeepPink4"] = RGBA( 0.545098039215686, 0.0392156862745098, 0.313725490196078 );
    colors["HotPink1"] = RGBA( 1, 0.431372549019608, 0.705882352941177 );
    colors["HotPink2"] = RGBA( 0.933333333333333, 0.415686274509804, 0.654901960784314 );
    colors["HotPink3"] = RGBA( 0.803921568627451, 0.376470588235294, 0.564705882352941 );
    colors["HotPink4"] = RGBA( 0.545098039215686, 0.227450980392157, 0.384313725490196 );
    colors["pink1"] = RGBA( 1, 0.709803921568627, 0.772549019607843 );
    colors["pink2"] = RGBA( 0.933333333333333, 0.662745098039216, 0.72156862745098 );
    colors["pink3"] = RGBA( 0.803921568627451, 0.568627450980392, 0.619607843137255 );
    colors["pink4"] = RGBA( 0.545098039215686, 0.388235294117647, 0.423529411764706 );
    colors["LightPink1"] = RGBA( 1, 0.682352941176471, 0.725490196078431 );
    colors["LightPink2"] = RGBA( 0.933333333333333, 0.635294117647059, 0.67843137254902 );
    colors["LightPink3"] = RGBA( 0.803921568627451, 0.549019607843137, 0.584313725490196 );
    colors["LightPink4"] = RGBA( 0.545098039215686, 0.372549019607843, 0.396078431372549 );
    colors["PaleVioletRed1"] = RGBA( 1, 0.509803921568627, 0.670588235294118 );
    colors["PaleVioletRed2"] = RGBA( 0.933333333333333, 0.474509803921569, 0.623529411764706 );
    colors["PaleVioletRed3"] = RGBA( 0.803921568627451, 0.407843137254902, 0.537254901960784 );
    colors["PaleVioletRed4"] = RGBA( 0.545098039215686, 0.27843137254902, 0.364705882352941 );
    colors["maroon1"] = RGBA( 1, 0.203921568627451, 0.701960784313725 );
    colors["maroon2"] = RGBA( 0.933333333333333, 0.188235294117647, 0.654901960784314 );
    colors["maroon3"] = RGBA( 0.803921568627451, 0.16078431372549, 0.564705882352941 );
    colors["maroon4"] = RGBA( 0.545098039215686, 0.109803921568627, 0.384313725490196 );
    colors["VioletRed1"] = RGBA( 1, 0.243137254901961, 0.588235294117647 );
    colors["VioletRed2"] = RGBA( 0.933333333333333, 0.227450980392157, 0.549019607843137 );
    colors["VioletRed3"] = RGBA( 0.803921568627451, 0.196078431372549, 0.470588235294118 );
    colors["VioletRed4"] = RGBA( 0.545098039215686, 0.133333333333333, 0.32156862745098 );
    colors["magenta1"] = RGBA( 1, 0, 1 );
    colors["magenta2"] = RGBA( 0.933333333333333, 0, 0.933333333333333 );
    colors["magenta3"] = RGBA( 0.803921568627451, 0, 0.803921568627451 );
    colors["magenta4"] = RGBA( 0.545098039215686, 0, 0.545098039215686 );
    colors["orchid1"] = RGBA( 1, 0.513725490196078, 0.980392156862745 );
    colors["orchid2"] = RGBA( 0.933333333333333, 0.47843137254902, 0.913725490196078 );
    colors["orchid3"] = RGBA( 0.803921568627451, 0.411764705882353, 0.788235294117647 );
    colors["orchid4"] = RGBA( 0.545098039215686, 0.27843137254902, 0.537254901960784 );
    colors["plum1"] = RGBA( 1, 0.733333333333333, 1 );
    colors["plum2"] = RGBA( 0.933333333333333, 0.682352941176471, 0.933333333333333 );
    colors["plum3"] = RGBA( 0.803921568627451, 0.588235294117647, 0.803921568627451 );
    colors["plum4"] = RGBA( 0.545098039215686, 0.4, 0.545098039215686 );
    colors["MediumOrchid1"] = RGBA( 0.87843137254902, 0.4, 1 );
    colors["MediumOrchid2"] = RGBA( 0.819607843137255, 0.372549019607843, 0.933333333333333 );
    colors["MediumOrchid3"] = RGBA( 0.705882352941177, 0.32156862745098, 0.803921568627451 );
    colors["MediumOrchid4"] = RGBA( 0.47843137254902, 0.215686274509804, 0.545098039215686 );
    colors["DarkOrchid1"] = RGBA( 0.749019607843137, 0.243137254901961, 1 );
    colors["DarkOrchid2"] = RGBA( 0.698039215686274, 0.227450980392157, 0.933333333333333 );
    colors["DarkOrchid3"] = RGBA( 0.603921568627451, 0.196078431372549, 0.803921568627451 );
    colors["DarkOrchid4"] = RGBA( 0.407843137254902, 0.133333333333333, 0.545098039215686 );
    colors["purple1"] = RGBA( 0.607843137254902, 0.188235294117647, 1 );
    colors["purple2"] = RGBA( 0.568627450980392, 0.172549019607843, 0.933333333333333 );
    colors["purple3"] = RGBA( 0.490196078431373, 0.149019607843137, 0.803921568627451 );
    colors["purple4"] = RGBA( 0.333333333333333, 0.101960784313725, 0.545098039215686 );
    colors["MediumPurple1"] = RGBA( 0.670588235294118, 0.509803921568627, 1 );
    colors["MediumPurple2"] = RGBA( 0.623529411764706, 0.474509803921569, 0.933333333333333 );
    colors["MediumPurple3"] = RGBA( 0.537254901960784, 0.407843137254902, 0.803921568627451 );
    colors["MediumPurple4"] = RGBA( 0.364705882352941, 0.27843137254902, 0.545098039215686 );
    colors["thistle1"] = RGBA( 1, 0.882352941176471, 1 );
    colors["thistle2"] = RGBA( 0.933333333333333, 0.823529411764706, 0.933333333333333 );
    colors["thistle3"] = RGBA( 0.803921568627451, 0.709803921568627, 0.803921568627451 );
    colors["thistle4"] = RGBA( 0.545098039215686, 0.482352941176471, 0.545098039215686 );
    colors["dark grey"] = RGBA( 0.662745098039216, 0.662745098039216, 0.662745098039216 );
    colors["DarkGrey"] = RGBA( 0.662745098039216, 0.662745098039216, 0.662745098039216 );
    colors["dark gray"] = RGBA( 0.662745098039216, 0.662745098039216, 0.662745098039216 );
    colors["DarkGray"] = RGBA( 0.662745098039216, 0.662745098039216, 0.662745098039216 );
    colors["dark blue"] = RGBA( 0, 0, 0.545098039215686 );
    colors["DarkBlue"] = RGBA( 0, 0, 0.545098039215686 );
    colors["dark cyan"] = RGBA( 0, 0.545098039215686, 0.545098039215686 );
    colors["DarkCyan"] = RGBA( 0, 0.545098039215686, 0.545098039215686 );
    colors["dark magenta"] = RGBA( 0.545098039215686, 0, 0.545098039215686 );
    colors["DarkMagenta"] = RGBA( 0.545098039215686, 0, 0.545098039215686 );
    colors["dark red"] = RGBA( 0.545098039215686, 0, 0 );
    colors["DarkRed"] = RGBA( 0.545098039215686, 0, 0 );
    colors["light green"] = RGBA( 0.564705882352941, 0.933333333333333, 0.564705882352941 );
    colors["LightGreen"] = RGBA( 0.564705882352941, 0.933333333333333, 0.564705882352941 );
  }

}
