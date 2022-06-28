# James O'Connell jgo2nja
# This program takes data from internet separated-value files and manipulates them to give a student information on
# classes and availability

def instructor_lectures(department, instructor):
    """
    :param department: The department for which course information applies.
    :param instructor: The instructor for which course information will be obtained.
    :return: A list of courses that are taught by the instructor, whether with or without other instructors.
    This function finds all classes taught by an instructor for a given department and returns them in a list.
    """
    import urllib.request
    url = 'http://cs1110.cs.virginia.edu/files/louslist/' + str(department)
    text = urllib.request.urlopen(url)
    course_list = []
    for line in text:
        line_decode = line.decode("utf-8")
        workable_line = line_decode.strip().split('|')
        if (instructor in workable_line[4]) and (workable_line[5] == "Lecture") and \
                (workable_line[3] not in course_list):
            course_list.append(workable_line[3])
    return course_list


def compatible_classes(first_class, second_class, needs_open_space=False):
    """
    :param first_class: The first class to be compared (Department ID, Course Number, Section).
    :param second_class: The second class to be compared (Department ID, Course Number, Section).
    :param needs_open_space: Boolean that represents whether open enrollment space is necessary in the comparison.
    :return: A boolean indicating whether it is possible to take both first_class and second_class.
    This function determines whether two classes can make a legitimate schedule together, and if they are full or not.
    """
    import urllib.request
    class_type = first_class.split(" ")
    class_type_second = class_type[1].split("-")
    class_type1 = second_class.split(" ")
    class_type1_second = class_type1[1].split("-")
    url = 'http://cs1110.cs.virginia.edu/files/louslist/' + str(class_type[0])
    url1 = 'http://cs1110.cs.virginia.edu/files/louslist/' + str(class_type1[0])
    text = urllib.request.urlopen(url)
    text1 = urllib.request.urlopen(url1)
    class1 = []
    for line in text:
        line_decode = line.decode("utf-8")
        workable_line = line_decode.strip().split('|')
        if (workable_line[1] == class_type_second[0]) and (workable_line[2] == class_type_second[1]):
            class1 = workable_line
    class2 = []
    for line in text1:
        line_decode = line.decode("utf-8")
        workable_line = line_decode.strip().split('|')
        if (workable_line[1] == class_type1_second[0]) and (workable_line[2] == class_type1_second[1]):
            class2 = workable_line
    print(class1)
    print(class2)
    switch = "on"
    order_list = [int(class1[12]), int(class2[12])]
    order_list1 = [int(class1[13]), int(class2[13])]
    early_class_end = min(order_list1)
    late_class_start = max(order_list)
    for day in range(7, 12):
        if class1[day] == "true" and class2[day] == "true":
            if early_class_end >= late_class_start:
                switch = "off"
    class_list = [class1, class2]
    for item in class_list:
        if needs_open_space and int(item[15]) >= int(item[16]):
            switch = "off"
    if switch == "off":
        return False
    else:
        return True
