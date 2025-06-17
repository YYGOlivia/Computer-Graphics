/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/. */

#define BOOST_TEST_MODULE testRenderer

#ifndef BOOST_TEST_DYN_LINK
#define BOOST_TEST_DYN_LINK
#endif

#include <boost/test/unit_test.hpp>
#include <objReader.hpp>
#include <core.hpp>


#include <map>
#include <string>
#include <optional>


BOOST_AUTO_TEST_SUITE(test_parsing)

BOOST_AUTO_TEST_CASE(test_parse_face)
{
     const std::map<std::string, std::optional<face>> test {{"f 12 13 1", face(12, 13, 1)},
                                         {"f 12/13 13/1 1/5", face(12, 13, 1)},
                                         {"f 12/13/1 13/1/5 1/5/9",face(12, 13, 1)},
                                         {"f 12//1 13//5 1//9", face(12, 13, 1)},
                                         {"f 12/13 1 5", std::nullopt},
                                         {"f 12/12/12 13/32/32 1/2332/332", face(12, 13, 1)},
                                         {"f 12//15 13//302 1//3200", face(12, 13, 1),},
                                         {"not a face", std::nullopt}};

    for(const auto&[str, res] : test)
    {
        if(!res.has_value())
        {
            BOOST_CHECK_THROW(parseFaceString(str), std::invalid_argument);
        }
        else
        {
            BOOST_CHECK_EQUAL(parseFaceString(str), res.value());
        }
    }
}

BOOST_AUTO_TEST_CASE(test_parse_vertex)
{
    const auto epsilon{0.0001f};
     const std::map<std::string, std::optional<point3d>> testVertices {
         {"v 505.000 264.000 41.356", point3d(505.000f, 264.000f, 41.356f)},
         {"v -0.078125 0.242188 0.656250", point3d{-0.078125f, 0.242188f, 0.656250}},
         {"v -7.8125e-2 2.42188e-001 -1.01603e1", point3d{-0.078125f, 0.242188f, -10.1603f}},
         {"v -7.8125e-2 0.242188 -1.01603e1", point3d{-0.078125f, 0.242188f, -10.1603f}},
         {"f -0.078125 0.242188 0.656250", std::nullopt},
         {"v -10.1603 5.71902 -0.957758", point3d(-10.1603f, 5.71902f, -0.957758f)},
         {"v 2.422296 -1.510915 -0.494169", point3d(2.422296f, -1.510915f, -0.494169f)},
         {"v 2.422296 -1.510915e -0.494169", std::nullopt},
         {"", std::nullopt,},
         {"not a vertex", std::nullopt}
    };

    for(const auto& [str, res] : testVertices)
    {
        if(!res.has_value())
        {
            BOOST_CHECK_THROW(parseVertexString(str), std::invalid_argument);
        }
        else
        {
            const auto vertex = parseVertexString(str);
            BOOST_CHECK_CLOSE(vertex.x, res.value().x, epsilon);
            BOOST_CHECK_CLOSE(vertex.y, res.value().y, epsilon);
            BOOST_CHECK_CLOSE(vertex.z, res.value().z, epsilon);
        }
    }
}


BOOST_AUTO_TEST_SUITE_END()